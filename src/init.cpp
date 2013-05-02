#include <cstdlib> // malloc, exit:
#include <sys/sem.h> // sudo ipcrm -M 0x0410669190
//#include <errno.h>  // just use perror("blah")! Adds errorstr(errno) automagically
//#include <sys/types.h>
//#include <sys/ipc.h>
#include <sys/shm.h>


//Since using #include <stdlib.h> dumps all declared names in the global namespace,
//the preference should be to use #include <cstdlib>, unless you need compatibility with C
#include <cstdlib>
//#include <stdlib.h> // system(cmd)

#include <string.h>
#include "util.hpp"
#include "netbase.hpp"
#include "init.hpp"
#include "relations.hpp"

/* attach to the segment to get a pointer to it: */
//const void * shmat_root = (const void *) 0x101000000; // mac 64 bitpointer to it: */
const void * shmat_root = (const void *) 0x110000000; // just higher than system Recommendation
//const void * shmat_root = (const void *)0x105800000;//test

bool virgin_memory = false;

#ifndef HAS_UNION_SEMUN
#ifdef USE_SEMCTL_SEMUN
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};
#endif
#endif
int semrm(key_t key, int id = 0) {
	union semun arg;
	id = semget(key, 0, 0);
	if (id == -1)
		return -1;
	return semctl(id, 0, IPC_RMID, arg);
}

int share_memory() {
	if (root_memory) {
		ps("root_memory already attached!");
		return 0;
	}
	/* make the key: */
	int key = 0x0410669190; //0x57020303;// #netbase ftok("netbase", 'RW');
	int shmid;
	//                virgin_memory=0;
	int READ_WRITE=0666;//
	if ((shmid = shmget(key, sizeOfSharedMemory, READ_WRITE)) == -1) {
		ps("share_memory used for the first time");
		virgin_memory = 1;
		if ((shmid = shmget(key, sizeOfSharedMemory, READ_WRITE | IPC_CREAT)) == -1){
			semrm(key); // clean and try again
		if ((shmid = shmget(key, sizeOfSharedMemory, READ_WRITE | IPC_CREAT)) == -1) {
			perror("share_memory failed: shmget! Not enough memory?");
//			printf("try calling ./clear-shared-memory.sh\n");
			//			perror(strerror(errno)); <= ^^ redundant !!!
			printf("try ipcclean && sudo ipcrm -M 0x0410669190");
			system("sudo ipcrm -M 0x0410669190");
			system("sudo sysctl -w kern.sysv.shmmax=2147483648");// # 2GB !!
			system("sudo sysctl -w kern.sysv.shmall=2147483648");
		}
		if ((shmid = shmget(key, sizeOfSharedMemory, READ_WRITE | IPC_CREAT)) == -1) {
			perror("share_memory failed: shmget! Not enough memory?");
			exit(1);
		}
		}
	}
	root_memory = (char *) shmat(shmid, (const void *) shmat_root, 0);
	if (root_memory == 0 || root_memory == (void *) (-1)) {//virgin_memory=1;
		ps("receiving other share_memory address");
		root_memory = (char *) shmat(shmid, (const void *) 0, 0); //void
	}
	if (root_memory == 0 || root_memory == (void *) (-1)) {
		perror("share_memory failed: shmat! Not enough memory?");
		exit(1);
	}
	Context* c = currentContext(); // getContext(node->context);
	if ((char*) root_memory != (char*) shmat_root) {// 64 BIT : %x -> %016llX
		printf("FYI: root_memory != desired shmat_root %016llX!=%016llX \n", root_memory, shmat_root);
		fixPointers();
	}
	char* msg = "share_memory root address = %016llX	size = %x	max = %016llX\n";
	printf(msg, root_memory, sizeOfSharedMemory, (char*) root_memory + sizeOfSharedMemory);
	contexts = (Context*) root_memory;
	abstracts = (Ahash*) (root_memory + abstractsOffset); // reuse or reinit
	extrahash = (Ahash*) (root_memory + abstractsOffset + abstractHashSize);
	checkRootContext();
	return 0;
}

long getMemory() {
	//long phypz = sysconf(_SC_PHYS_PAGES);
	//long psize = sysconf(_SC_PAGE_SIZE);
	//return phypz*psize;
}

long GetAvailableMemory(void) {
	void *p, *q;
	long siz = 10000000;
	q = p = calloc(1, siz);
	while (q) {
		siz = siz * 1.2; // Can be more to speed up things
		q = realloc(p, siz);
		if (q)// infinite virtual mem :{ 31107287834197
			p = q;
	}
	free(p);
	return siz;
}

// modify char* in vivo / inline!



void initRootContext(){
	Context* rootContext=(Context*)root_memory;
	memset(contexts, 0, contextOffset);// ? why only?
	initContext(rootContext);
//	if(rootContext)
	strcpy(rootContext->name,"ROOT CONTEXT");
	rootContext->id=1;// not virgin_memory any more
	rootContext->nodes=(Node*)&root_memory[contextOffset];
	rootContext->statements=(Statement*)&root_memory[contextOffset+nodeSize * maxNodes];
}

void checkRootContext(){
	Context* rootContext=(Context*)root_memory;
	if(rootContext->id!=1){
		p("STARTING WITH CLEAN MEMORY");
		initRootContext();
//		clear();
		return;
	}

	p("USING SHARED MEMORY");
	if(rootContext->nodes!=(Node*)&root_memory[contextOffset]){
		showContext(rootContext);
		fixPointers();
	}
	if(currentContext()->nodes!=rootContext->nodes)
		fixPointers();
}

void init() {
    int i;
    //    if ((i = setjmp(try_context)) == 0) {// try once
    share_memory();
    getContext(current_context);
//    initContext(&contexts[current_context]);
    initRelations();
//	collectAbstracts();// zur sicherheit
//    if(!hasWord("m^2"))
//        initUnits();
    if(currentContext()->nodeCount<100)currentContext()->nodeCount=10000;
    showContext(current_context);
    //    }if (i == 128) {printf("recovered EXC_BAD_ACCESS !\n");}// catch
}


void fixNodes(Context* context, Node* oldNodes) {
	int max = context->statementCount; // maxStatements;
	for (int i = 0; i < max; i++) {
		Statement* n = &context->statements[i];

		if(!checkStatement(n)){
			showStatement(n);continue;
		}
		//		if(n==null || n->id==0 || n->context==0)
		//			continue;
		//			n->Subject=n->Subject-oldNodes+context->nodes;
		//			n->Predicate=n->Predicate-oldNodes+context->nodes;
		//			n->Object=n->Object-oldNodes+context->nodes;
		n->Subject = &context->nodes[n->subject];
		n->Predicate = &context->nodes[n->predicate];
		n->Object = &context->nodes[n->object];
		//		    n->name=n->name-oldnodeNames+c->nodeNames;
	}
}

void load(bool force) {

	clock_t start = clock();
	double diff;
	//  diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;

	Context* c = currentContext();
	//    showContext(c->id);
	Node* oldNodes = c->nodes;
	char* oldnodeNames = c->nodeNames;
	oldnodeNames = initContext(c);

	//  #include <sys/stat.h>
	//  struct stat stFileInfo;
	//  int intStat = stat((path+ "contexts.bin").data(),&stFileInfo);
	//  if(intStat != 0) { p("file not found");}
	//
	if (!force && root_memory) {//&&root_memory[1000]!=0){// first id==0
		//        pi(root_memory[0]);
		ps("loaded from shared memory");
		if (virgin_memory || !hasWord("Member"))
			collectAbstracts(); //or load abstracts->bin
		showContext(wordnet);
		return;
	}

	ps("Loading graph from files!");

	FILE *fp;
	printf("Opening File %s\n", (path + "contexts.bin").data());
	if ((fp = fopen((path + "contexts.bin").data(), "rb")) == NULL) {
		perror("Error opening file");
		p("starting with fresh context!");
		//        exit(1);
	} else {
		fread(contexts, sizeof (Context), maxContexts, fp);
		fclose(fp);
	}
	//    fp=fopen("wordnet.bin", "rb");
	//    fread(c, sizeof(Context), 1, fp);
	//    fclose (fp);

	fp = fopen((path + "names.bin").data(), "rb");
	fread(c->nodeNames, sizeof (char), c->currentNameSlot + 100, fp);
	fclose(fp);

	fp = fopen((path + "statements.bin").data(), "rb");
	fread(c->statements, sizeof (Statement), c->statementCount, fp); //c->statementCount maxStatements
	fclose(fp);

	fp = fopen((path + "nodes.bin").data(), "rb");
	fread(c->nodes, sizeof (Node), c->nodeCount, fp);

	//
	//    fp = fopen((path+"abstracts->bin").data(), "rb");
	//    fread(abstracts, sizeof (Node), c->nodeCount, fp);

	//    showContext(c);

#ifndef inlineName
	if (oldnodeNames != c->nodeNames) {
		p("Fixing nodeNames");
		fixNodeNames(c, oldnodeNames);
		//        init();// to get back relations CAREFUL!
	}
#endif

	if (oldNodes != c->nodes) {
		p("Fixing nodes");
		fixNodes(c, oldNodes);
	}

	collectAbstracts(); //or load abstracts->bin

	//    initContext(c);//
	//
	//
	//    fp=fopen("test.bin", "rb");
	//    if(fp)fread(test, sizeof(char), 100, fp);
	//   fclose (fp);

	//  cout<<"nanoseconds "<< diff <<'\n';
}

void fixPointers() {
	Context* context = (Context*) root_memory;
	showContext(context);
	fixPointers(context);
	showContext(context);
	context = currentContext();// &contexts[wordnet]; // todo: all
	showContext(context);
	fixPointers(context);
	showContext(context);
	collectAbstracts();
}

void fixPointers(Context* context) {
	p("ADJUSTING SHARED MEMORY");
	Node* oldNodes = context->nodes;
	char* oldNames = context->nodeNames;
	initContext(context);
	check((char*) context->nodes == root_memory + contextOffset);
	//	context->nodes=root_memory
	fixNodes(context, oldNodes);
	fixNodeNames(context, oldNames);
}



int collectAbstracts() {
	ps("collecting abstracts");
	initRelations();
	abstracts = (Ahash*) (&root_memory[abstractsOffset]);
	extrahash = (Ahash*) (&root_memory[abstractsOffset + abstractHashSize]);
	memset(abstracts, 0, abstractHashSize);
	memset(extrahash, 0, abstractHashSize);
	Context* c = currentContext();
	int max = c->nodeCount; // maxNodes;
	int count = 0;
	// collect Abstracts
	for (int i = 0; i < max; i++) {
		Node* n = &c->nodes[i];
		if (i > 1000 && !checkNode(n))break;
		if (n == null || n->name == null || n->id == 0 || n->context == 0)
			continue;
		if (n->kind == Abstract->id) {
			//			if(eq(n->name,"city"))
			//				max--;
			insertAbstractHash(n);
			count++;
		}
	}
	return count;
}

void fixNodeNames(Context* context, char* oldnodeNames) {

#ifdef inlineName
	printf("inlineNames!");
	return;
#endif
	int max = context->nodeCount; // maxNodes;
	long newOffset= context->nodeNames- oldnodeNames;
	for (int i = 0; i < max; i++) {
		Node* n = &context->nodes[i];
//		show(n,true);
		if (n == null || n->name == null || n->id == 0 || n->context == 0)
			continue;
#ifndef inlineName
		n->name = n->name + newOffset;
#endif

	}
}

void clearMemory(){
	ps("Cleansing Memory!");
    memset(root_memory,0,sizeOfSharedMemory);
	initRootContext();
//		Context* context=currentContext();
//        memset(context->nodes, 0, nodeSegmentSize ); //calloc!
//        memset(contextnodeNames, 0, nameSegmentSize);
//        memset(contextstatements, 0, statementSegmentSize);
//        memset(abstracts, 0, abstractHashSize);
//        memset(extrahash, 0, abstractHashSize);
}


char* initContext(Context* context) {
    printf("Initiating context %d\n", context->id);
    Node* nodes = 0;
    Statement* statements = 0;
    char* nodeNames = 0;
	int nodeSize=sizeof (Node);// 40
	int statementSize=sizeof (Statement);//
	int ahashSize=sizeof (Ahash);//
//    int contextOffset=sizeof (Context) *maxContexts;
    long nameSegmentSize = sizeof (char) * averageNameLength * maxNodes;
    long nodeSegmentSize = nodeSize * maxNodes;
    long statementSegmentSize = statementSize * maxStatements0;
	long abstractOffset = contextOffset+nodeSegmentSize + nameSegmentSize + statementSegmentSize; //just put them at the end!!
    if (root_memory) {
        if (contextOffset+nodeSegmentSize + nameSegmentSize + statementSegmentSize + abstractHashSize*2 > sizeOfSharedMemory){
	    ps("ERROR sizeOfSharedMemory TOO SMALL!");
            ps("contextOffset+nodeSegmentSize+nameSegmentSize+statementSegmentSizeabstractSegment+2*abstractHashSize > sizeOfSharedMemory !");
            pl(contextOffset+nodeSegmentSize + nameSegmentSize + statementSegmentSize + abstractHashSize*2);
            pi(sizeOfSharedMemory);
            exit(1);
        }
        nodes = (Node*) (root_memory+contextOffset);
        nodeNames = (char*) &root_memory[contextOffset+nodeSegmentSize];
	    statements = (Statement*) &root_memory[contextOffset+nodeSegmentSize + nameSegmentSize];
        abstracts = (Ahash*) &root_memory[abstractOffset];
        extrahash = (Ahash*) &root_memory[abstractOffset + abstractHashSize];// noch mal so viele: im ø 2 Ahashs / wort?
    } else do {
            statements = (Statement*) malloc(statementSegmentSize + 1);
            nodes = (Node*) malloc(nodeSegmentSize + 1);
            nodeNames = (char*) malloc(nameSegmentSize + 1);
            //        nodeNames=(char*)malloc(sizeof(char)*nameBatch);// incremental
            if (nodes == 0 || statements == 0 || nodeNames == 0) {
                ps("System has not enough memory to support ");
                printf("%d Nodes and %d Statements\nDividing by 2 ...\n", maxNodes, maxStatements0);
                maxStatements0 = maxStatements0 / 2;
                maxNodes = maxNodes / 2;
                // negotiate memory cleverly!!
            }
        } while (nodes == 0 || statements == 0);
    if (!root_memory || virgin_memory)
		clearMemory();
    Statement* oldstatements = context->statements;
    char* oldnodeNames = context->nodeNames;
    Node* oldnodes = context->nodes;
    context->nodes = nodes;
    context->statements = statements;
    context->nodeNames = nodeNames;
	px(context);
	px(nodes);
	px(nodeNames);
	px(statements);
	px(abstracts);
	px(extrahash);
//		check((Node*)nodeNames==&context->nodes[maxNodes]);// statements == bounds of nodes
    return oldnodeNames;
}


#ifdef sharedLib
/* The shared library's read-only segment (in particular, its .text section) can be shared among all processes;
 * while its write-able sections (such as .data and .bss) can be allocated uniquely for each executing process.
 * This write-able segment is also referred to as the object's Static Data Segment.
 * It is this static data segment that creates most of the complexity for the implementation of shared libraries.
http://www.cadenux.com/xflat/NoMMUSharedLibs.html#shlibs  */
//#define sharedLib

void __attribute__((constructor)) my_init(void) {
	if (debug)
		printf("loading shared library \n");
	share_memory();
	if (root_memory[0] != 1)
		buildDictionary(); //4sec.
	else if (debug)
		printf("attached to shared memory of library libDictionary.so \n");
	// saveDictionary();
	// loadDictionary();
	return 0;
}
#endif
