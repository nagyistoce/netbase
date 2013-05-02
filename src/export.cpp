#include "netbase.hpp"
#include "util.hpp"
#include <sys/stat.h> // mkdir
void save() {
    Context* c = currentContext();

    FILE *fp;
    fp = fopen((path+"statements.bin").data(), "wb");
    fwrite(c->statements, sizeof (Statement), c->statementCount, fp);
    fclose(fp);

    fp = fopen((path+"nodes.bin").data(), "wb");
    fwrite(c->nodes, sizeof (Node), c->nodeCount, fp);
    fclose(fp);

    fp = fopen((path+"names.bin").data(), "wb");
    fwrite(c->nodeNames, sizeof (char), c->currentNameSlot + 100, fp);
    fclose(fp);

    fp = fopen((path+"contexts.bin").data(), "wb");
    fwrite(contexts, sizeof (Context), maxContexts, fp);
    fclose(fp);

//    fp = fopen((path+"wordnet.bin").data(), "wb");
//    fwrite(c, sizeof (Context), 1, fp);
//    fclose(fp);
//
//    fp = fopen((path+"abstracts.bin").data(), "wb");
//    fread(abstracts, sizeof (Node), c->nodeCount, fp);// todo
//    fclose(fp);

    ps("context saved!");

    //    fp=fopen("test.bin", "wb");
    //    fwrite(test, sizeof(char), 100, fp);
    //    fclose (fp);
}

// what for??
void export_csv(){
    Context* c = currentContext();
    FILE *fp;
	// To write numbers in octal, precede the value with a 0. Thus, 023 is 238 (which is 19 in base 10).
	mkdir((path+"export").c_str(),0777);
    fp = fopen((path+"export/nodes.csv").data(), "w");
	if(!fp){
		ps("CANT ACCESS "+(path+"export/nodes.csv"));
		return;
	}
    for (int i = 0; i < c->nodeCount; i++) {
        Node* n= &c->nodes[i];
		if(!checkNode(n,i))continue;
        fprintf(fp,"%d\t%s\n",n->id,n->name);
//        fprintf("%d\t%s\t%d",n->id,n->name,n->kind);//n->context
    }
    fp = fopen((path+"export/statements.csv").data(), "w");
    for (int i = 0; i < c->statementCount; i++) {
        Statement* n= &c->statements[i];
		if(!checkStatement(n,true,false))continue;
        fprintf(fp,"%d\t%d\t%d\n",n->subject,n->predicate,n->object);//,n->kind);//n->context
    }

    // what for?
    // for 'debugging' ?
    // only makes sense with 'no ambiguity names' apple_(tree), in_(location), ...
    fp = fopen((path+"export/statement-names.csv").data(), "w");
    for (int i = 0; i < c->statementCount; i++) {
        Statement* n= &c->statements[i];
		if(!checkStatement(n,true,true))continue;
		if(n->Predicate==Instance)continue;
        fprintf(fp,"%s\t%s\t%s\n",n->Subject->name,n->Predicate->name,n->Object->name);//,n->kind);//n->context
    }
    fclose(fp);

    ps("context CSV saved!");

}
