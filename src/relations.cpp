        /*
 * File:   relations.cpp
 * Author: me
 *
 * Created on March 28, 2012, 10:25 PM
 */
#include "util.hpp"
#include "relations.hpp"
// DONT depend on netbase!
Node* Error;
Node* Unknown;
Node* Antonym;
Node* Parent;
Node* SuperClass; // Parent
// Node* IsA;// Parent
Node* SubClass;
Node* Cause;
Node* Entailment; // Implication
Node* Owner; //Owner inverse Member   (Prince of Persia) <=> (Persia has Prince)
Node* Member;
Node* Part;
Node* PartOf;
Node* Substance;
Node* Synonym;
Node* Domain;
Node* PERTAINYM;
Node* Weight;
Node* Type;
Node* Instance;

Node* Active;
Node* Passive;
Node* Tag;
Node* Label;
Node* BackLabel;
Node* Comment;
Node* Labels;
Node* LabeledNode;
Node* Category;
Node* SubContext;
Node* SuperContext;

// Types
Node* Internal;
Node* _Node;
Node* Thing;
Node* Item;
Node* Abstract; // Thing
Node* Class;
Node* Object;
Node* Relation;
Node* Reification;
Node* Property;
Node* Pattern; // temporary

Node* Any;
// Semantics
Node* Attribute; //ok, if  Node* Attribute declared in netbase.cpp
// Node* Is; // danger: obama is president etc

Node* Person;
Node* Adjective;
Node* Noun;
Node* Verb;
Node* Adverb;

Node* Derived;// Adjective^-1
Node* DerivedFromNoun;

Node* Number;
Node* Double;// == Number
Node* Float;// == Number

Node* Integer;
Node* Long;// == Integer

Node* String;
Node* Date;

Node* Bytes;// byte[] -> serialized java object etc etc
Node* Map; // Map<String,T>
Node* Array;// T[]
Node* List; // List<T>

Node* Range;
Node* Unit;

Node* True;
Node* False;

Node* Translation;
Node* Plural;
Node* And;
Node* Or;
Node* Not;

//There are about 150 prepositions in English
Node* Of; // ==owner
Node* In; // ==location,...
Node* To; // ==direction,<object>
Node* From;
Node* By;
Node* For;
Node* On;


Node* Equals;
Node* Greater;
Node* More;
Node* Smaller;
Node* Less; //smaller
Node* Between;
Node* Circa;
Node* Much;
Node* Little;
Node* Very;
Node* Contains;
Node* StartsWith;
Node* EndsWith;

Node* UsageContext;



Node* addRelation(int id, const char* name,bool transitive=false) {
	Node* n = add_force(wordnet, id, name, _internal);
    insertAbstractHash(wordhash(name), n);// ECHT? TYP ?
//	if(n->statementCount==0&&id>0)// IT BETTER BE!!!
//		addStatement4(wordnet, getAbstract(name)->id,_instance,id);// Internal
//	if(transitive)???  baked into Algorithms, at least four standard relations?
	return n;
}

void initRelationsDE() {
//	Unknown = addRelation(_see, "siehe");
	Unknown = addRelation(_see, "?");
	Antonym = addRelation(_antonym, "Gegenteil");
	Error = addRelation(_error, "Fehler");
    //	Part = addRelation(1, "part"); USA etc BUG!?!!
	Attribute = addRelation(_attribute, "Attribut"); // tag
	Property=Attribute;
	bool is_transitive=true;
	Cause = addRelation(_cause, "Grund",is_transitive); //
	Derived =addRelation(_derived, "Abgeleitet"); //
    //	DerivedFromNoun =addRelation(_derived_from_noun, "derived from noun"); //
	//        DOMAIN_OF_SYNSET_CATEGORY =
	UsageContext=addRelation(_DOMAIN_CATEGORY, "Kontext"); // # sheet @ maths   // think of!! OWNER -> Part
	//    DOMAIN_OF_SYNSET_REGION =
	addRelation(_DOMAIN_REGION, "Region"); // mate @ australia
	//    DOMAIN_OF_SYNSET_USAGE =
	Domain=addRelation(_DOMAIN_USAGE, "Bereich"); // #bitch @ colloquialism  || fin de siecle @ French   # fuck(vulgar)
	//    ENTAILMENT =
	addRelation(_ENTAILMENT, "Impliziert",is_transitive); //ENTAILMENT  jump implies come down
	SuperClass = addRelation(_Hypernym, "Klasse",is_transitive); //Parent ,"Hypernym"
	Parent = SuperClass;
	//	IsA = SuperClass;
    
	SubClass = addRelation(_hyponym, "Unterklasse",is_transitive); // hyponym
	Owner = addRelation(_Owner, "von",is_transitive);
	Member = addRelation(_Member, "hat");
	//	MEMBER_OF_THIS_DOMAIN_CATEGORY=
	addRelation(_MEMBER_DOMAIN_CATEGORY, "contextual"); //aviation: to overfly
	//	MEMBER_OF_THIS_DOMAIN_REGION =
	addRelation(_MEMBER_DOMAIN_REGION, "regional"); //-r  IN Japan :  Sushi
	//	MEMBER_OF_THIS_DOMAIN_USAGE =
	addRelation(_MEMBER_DOMAIN_USAGE, "Domaine"); // colloquialism: bitch
	PartOf = addRelation(_PartOf, "Teil von",is_transitive);
	Part = addRelation(_Part, "Teil",is_transitive);
	//	PARTICIPLE_OF_VERB =
	addRelation(_PARTICIPLE_OF_VERB, "Partizip");
	PERTAINYM =addRelation(_PERTAINYM, "Abgeleitet"); //  # cellular(a) \ cell(n) 	equally(adv)-equal(adj)
	Synonym = addRelation(_synonym, "Synonym",is_transitive); // similar?? 32??
	addRelation(_SubstanceOwner, "Substanz von",is_transitive);
	Substance = addRelation(_Substance, "Substanz",is_transitive);
	addRelation(_VERB_GROUP, "Verb Gruppe");
	//	RELATIONSHIP_COUNT =
    //	addRelation(25, "RELATIONSHIP_COUNT");
	addRelation(97, "Domaine");
	addRelation(98, "Hat");
	//	 Synonym = Relation(32, "synonym");// -> 21????? See see | tag
	Type = addRelation(_Type, "Typ");// is_transitive?? // (instance->class) !=SuperClass
	Instance = addRelation(_instance, "Instanz",is_transitive);
    
   	Weight = addRelation(31, "Gewicht");
	Active = addRelation(35, "Activ");
	Passive = addRelation(36, "Passiv");
	Tag = addRelation(37, "tag"); // different to 'unknown' !!
	Label = addRelation(38, "Label");
	BackLabel = addRelation(39, "Label von");
	addRelation(40, "��hnlich");// hypernym?? no synonym
	addRelation(50, "auch");// hypernym??
	Category = addRelation(43, "Kategorie"); // tag
	SubContext = addRelation(44, "Subcontext"); // tag
	SuperContext = addRelation(45, "Supercontext"); //
	Comment = addRelation(46, "Kommentar");
    
	Internal = addRelation(_internal, "intern"); //ok
	_Node = addRelation(_node, "Knoten");
	Abstract = addRelation(_abstract, "Abstract");
	Class = addRelation(_clazz, "Klasse");
	Object = addRelation(_object, "Object");
	Relation = addRelation(_relation, "Relation");
	Pattern = addRelation(_pattern, "Muster");
	Reification = addRelation(_reification, "Reifikation");
    
	// Thing   = addRelation(101, "thing");
	// Item    = addRelation(101, "item");
	Person = addRelation(_person, "Person");
	Adjective = addRelation(adjective, "Adjective");
	Noun = addRelation(noun, "Nomen");
	Verb = addRelation(verb, "Verb");
	Adverb = addRelation(adverb, "Adverb");
	Number = addRelation(_number, "Zahl");
	Unit = addRelation(unit, "Einheit");
    
    Array = addRelation(_array, "Liste");
    List = addRelation(_list, "Liste");
    Map = addRelation(_map, "Hash");
    Bytes = addRelation(_bytes, "Daten");
    
	Plural = addRelation(_plural, "Plural");
	Translation = addRelation(translation, "��bersetzung");
    
	And = addRelation(_And, "Und");
	Or = addRelation(_Or, "Oder");
	Not = addRelation(_Not, "Nicht");
	Any = addRelation(_any, "*");
    
    
	Equals = addRelation(_Equals, "=");
	Greater = addRelation(_Greater, ">");
	More=Greater;
	Less = addRelation(_Less, "<"); //smaller
	Smaller=Less;
	Between = addRelation(_Between, "Between");
	Circa = addRelation(_Circa, "Circa");
	Much = addRelation(_Much, "much");
	Little = addRelation(_Much, "little");
	Very = addRelation(_Very, "very");
	Contains = addRelation(_Contains, "Contains");
	StartsWith = addRelation(_StartsWith, "starts with");
	EndsWith = addRelation(_EndsWith, "ends with");
    
	String = addRelation(_string, "String");
	Date = addRelation(_date, "Datum");
	Float = addRelation(_float, "Float");
	Integer = addRelation(_integer, "Integer");
	Range = addRelation(_range, "Bereich");
    
	True= addRelation(_true,"Wahr");
	False=addRelation(_false,"Falsch");// todo
}


void initRelations() {
//    if(testing){p("testing");return;}
    p("initRelations");
    currentContext()->currentNameSlot++;// not 0!
    if(germanLabels){initRelationsDE();return;}
	Unknown = addRelation(_see, "unknown");
    
	Any = addRelation(_any, "?");
    Error = addRelation(_error, "Error");
	Antonym = addRelation(_antonym, "antonym");
//	Part = addRelation(1, "part"); USA etc BUG!?!!
	Attribute = addRelation(_attribute, "attribute"); // tag
	Property=Attribute;
	bool is_transitive=true;
	Cause = addRelation(_cause, "cause",is_transitive); //
	Derived =addRelation(_derived, "derived"); //
//	DerivedFromNoun =addRelation(_derived_from_noun, "derived from noun"); //
	//        DOMAIN_OF_SYNSET_CATEGORY =
	UsageContext=addRelation(_DOMAIN_CATEGORY, "usage context"); // # sheet @ maths   // think of!! OWNER -> Part
	//    DOMAIN_OF_SYNSET_REGION =
	addRelation(_DOMAIN_REGION, "usage region"); // mate @ australia
	//    DOMAIN_OF_SYNSET_USAGE =
	Domain=addRelation(_DOMAIN_USAGE, "usage domain"); // #bitch @ colloquialism  || fin de siecle @ French   # fuck(vulgar)
	//    ENTAILMENT =
	addRelation(_ENTAILMENT, "entails",is_transitive); //ENTAILMENT  jump implies come down
	SuperClass = addRelation(_Hypernym, "superclass",is_transitive); //Parent ,"Hypernym"
	Parent = SuperClass;
	//	IsA = SuperClass;

	SubClass = addRelation(_hyponym, "subclass",is_transitive); // hyponym
	Owner = addRelation(_Owner, "of",is_transitive);
	Member = addRelation(_Member, "has");
	//	MEMBER_OF_THIS_DOMAIN_CATEGORY=
	addRelation(_MEMBER_DOMAIN_CATEGORY, "contextual word"); //aviation: to overfly
	//	MEMBER_OF_THIS_DOMAIN_REGION =
	addRelation(_MEMBER_DOMAIN_REGION, "regional word"); //-r  IN Japan :  Sushi
	//	MEMBER_OF_THIS_DOMAIN_USAGE =
	addRelation(_MEMBER_DOMAIN_USAGE, "domain word"); // colloquialism: bitch
	PartOf = addRelation(_PartOf, "part of",is_transitive);
	Part = addRelation(_Part, "part",is_transitive);
	//	PARTICIPLE_OF_VERB =
	addRelation(_PARTICIPLE_OF_VERB, "participle");
	PERTAINYM =addRelation(_PERTAINYM, "pertainym"); //  # cellular(a) \ cell(n) 	equally(adv)-equal(adj)

	Synonym = addRelation(_synonym, "synonym",is_transitive); // similar?? 32??
	//    Similar = addRelation(21, "similar");//synonym ??

	//	SubstanceOwner=
	addRelation(_SubstanceOwner, "substance of",is_transitive);
	Substance = addRelation(_Substance, "substance",is_transitive);
	//	VERB_GROUP=
	addRelation(_VERB_GROUP, "verb group");
	//	RELATIONSHIP_COUNT =
//	addRelation(25, "RELATIONSHIP_COUNT");
	addRelation(97, "domain");
	addRelation(98, "MEMBER");// ??


	Weight = addRelation(31, "weight");
	//	 Synonym = Relation(32, "synonym");// -> 21????? See see | tag
	Type = addRelation(_Type, "type");// is_transitive?? // (instance->class) !=SuperClass
	Instance = addRelation(_instance, "instance",is_transitive);
	Active = addRelation(35, "active");
	Passive = addRelation(36, "passive");
	Tag = addRelation(37, "tag"); // different to 'unknown' !!
	Label = addRelation(38, "label");
	BackLabel = addRelation(39, "label of");
	addRelation(40, "similar");// hypernym?? no synonym
	addRelation(50, "also");// hypernym??
	//	Labels = addRelation(40, "Label");//??
	//	LabeledNode = addRelation(41, "LabeledNode");// ?? ugly!!
	Category = addRelation(43, "category"); // tag
	SubContext = addRelation(44, "subcontext"); // tag
	SuperContext = addRelation(45, "supercontext"); //
	Comment = addRelation(46, "comment");

	// Node Types!
	/*
	31 Weight
	32 Unknown
	33 Type
	34 Instance
	35 Active
	36 Passive
	37 Tag
	38 Label
	39 BackLabel
	41 LabeledNode
	42 Attribute
	 */
	//Context= addRelation(99, "context");
	Internal = addRelation(_internal, "internal"); //ok
	_Node = addRelation(_node, "node");
	Abstract = addRelation(_abstract, "abstract");
	Class = addRelation(_clazz, "class");
	Object = addRelation(_object, "object");
	Relation = addRelation(_relation, "relation");
	Pattern = addRelation(_pattern, "pattern");
	Reification = addRelation(_reification, "reification");

	// Thing   = addRelation(101, "thing");
	// Item    = addRelation(101, "item");
	Person = addRelation(_person, "person");
	Adjective = addRelation(adjective, "adjective");
	Noun = addRelation(noun, "noun");
	Verb = addRelation(verb, "verb");
	Adverb = addRelation(adverb, "adverb");
	Number = addRelation(_number, "number");
	Unit = addRelation(unit, "unit");
    Array = addRelation(_array, "array");

	Plural = addRelation(_plural, "plural");
	Translation = addRelation(translation, "translation");

	And = addRelation(_And, "and");
	Or = addRelation(_Or, "or");
	Not = addRelation(_Not, "not");

	Equals = addRelation(_Equals, "=");
	Greater = addRelation(_Greater, ">");
	More=Greater;
	Less = addRelation(_Less, "<"); //smaller
	Smaller=Less;
	Between = addRelation(_Between, "Between");
	Circa = addRelation(_Circa, "Circa");
	Much = addRelation(_Much, "much");
	Little = addRelation(_Much, "little");
	Very = addRelation(_Very, "very");
	Contains = addRelation(_Contains, "Contains");
	StartsWith = addRelation(_StartsWith, "starts with");
	EndsWith = addRelation(_EndsWith, "ends with");

	String = addRelation(_string, "String");
	Date = addRelation(_date, "Date");
	Float = addRelation(_float, "Float");
	Integer = addRelation(_integer, "Integer");
    
    List = addRelation(_list, "List");
    Map = addRelation(_map, "Hash");
    Bytes = addRelation(_bytes, "Data");
	Array = addRelation(_array, "Array");
    
	Range = addRelation(_range, "Range");

	True= addRelation(_true,"True");
	False=addRelation(_false,"False");// todo
}

Node* invert(Node* relation) {
	if (relation == Unknown)return Unknown;
	if (relation == Antonym)return Antonym;
	if (relation == Parent)return SubClass; //?Instance;
	if (relation == SuperClass)return SubClass;
	if (relation == SubClass)return SuperClass;
	//if(relation==Cause)return ;
	//if(relation==Entailment)return ; // Implication
	if (relation == Owner)return Member;
	if (relation == Member)return Owner;
	if (relation == Part)return PartOf;
	if (relation == PartOf)return Part;
	if (relation == Substance)return PartOf; //?
	if (relation == Synonym)return Synonym;
	//if(relation==Weight)return ??;
	if (relation == Type)return Instance;
	if (relation == Instance)return Type;
	if (relation == Active)return Passive;
	if (relation == Passive)return Active;
	if (relation == Tag)return Tag; //gged
	if (relation == Label)return BackLabel;
	if (relation == BackLabel)return Label;
	if(relation==Labels)return LabeledNode;
	if(relation==LabeledNode)return Label;
	//if(relation==Category)return ;
	if (relation == SubContext)return SuperContext;
	if (relation == SuperContext)return SubContext;

	if (relation->id==40)return get(50);
	if (relation->id==50)return get(40);


	if (relation->id==97)return get(98);
	if (relation->id==98)return get(97);

	if (relation->id==_DOMAIN_CATEGORY)return get(_MEMBER_DOMAIN_CATEGORY);
	if (relation->id==_DOMAIN_REGION)return get(_MEMBER_DOMAIN_REGION);
	if (relation->id==_DOMAIN_USAGE)return get(_MEMBER_DOMAIN_USAGE);
	if (relation->id==_MEMBER_DOMAIN_CATEGORY)return get(_DOMAIN_CATEGORY);
	if (relation->id==_MEMBER_DOMAIN_REGION)return get(_DOMAIN_REGION);
	if (relation->id==_MEMBER_DOMAIN_USAGE)return get(_DOMAIN_USAGE);


	if (relation == Derived)return Derived;
//	if (relation == Derived)return Adjective;
//	if (relation == DerivedFromNoun)return Noun;

	if (relation == Equals)return Not;
	if (relation == Greater)return Less;
	if (relation == Less)return Greater;
	if (relation == Much)return Little;
	if (relation == Little)return Much;
	if (has(relation, Antonym, Any, false, false, false, false))
		return has(relation, Antonym);
	else return Unknown;// null; //! or relation .name + "OF" ?  weight => weight OF
}


// expansive! todo! merge later
Node * getRelation(const char* thing) {
	if (thing[0] == '#') thing++;
	if (eq(thing, "instance")) return Instance;
    if (eq(thing, "Contains")) return Part;
    if (eq(thing, "Broader")) return SuperClass;
    if (eq(thing, "Broader topic")) return SuperClass;
    if (eq(thing, "narrower")) return SubClass;
    if (eq(thing, "narrower topic")) return SubClass;
//    if (eq(thing, "Organism type")) return SuperClass;
    //    if (eq(thing, "Species")) return SuperClass;
    //    if (eq(thing, "Breed of")) return SuperClass;
//    Higher Classification
	if (eq(thing, "type")) return Type;// lustiger Typ !!! --------- !!!!!!!!
   	if (eq(thing, "has type")) return Type;
	if (eq(thing, "is")) return Type;
//   	if (eq(thing, "TEILVON")) return PartOf;
	if (eq(thing, "has")) return Member;
	if (eq(thing, "of")) return Owner;
   	if (eq(thing, "containedby")) return PartOf;
   	if (eq(thing, "partOf")) return PartOf;
	if (eq(thing, "by")) return Owner; // creator
	if (eq(thing, "type")) return Type;
	if (eq(thing, "property")) return Attribute; // Property;
	if (eq(thing, "inverseOf"))return Antonym;
	if (eq(thing, "reverse property"))return Antonym;
	if (eq(thing, "true"))return True;
	if (eq(thing, "false")) return False;
	if (eq(thing, "label")) return Label;
	if (eq(thing, "range")) return Range;
	if (eq(thing, "domain")) return Domain;
	if (eq(thing, "inverseOf")) return Antonym;
    
	if (eq(thing, "Typ")) return Type;
	if (eq(thing, "Art")) return Type;
//    if (eq(thing, "Klasse")) return SuperClass;

//	if (eq(thing, "reverse_property")) return Owner;
    
    
	//	if (eq(thing, "in"))return Loc;
	return 0;
}
