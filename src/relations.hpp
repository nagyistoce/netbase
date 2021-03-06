/*
 * File:   relations.hpp
 * Author: me
 *
 * Created on March 28, 2012, 7:49 PM
 */

#include "netbase.hpp"

#ifndef RELATIONS_HPP
#define	RELATIONS_HPP

extern Node* Unknown;
extern Node* Error;
extern Node* Missing;
extern Node* Antonym;
extern Node* Parent;
extern Node* SuperClass;// Parent
//extern Node* IsA;// Parent
extern Node* SubClass;
extern Node* Cause;
extern Node* Entailment; // Implication
extern Node* Owner;//Owner inverse Member   (Prince of Persia) <=> (Persia has Prince)
extern Node* Member;
extern Node* Part;
extern Node* PartOf;
extern Node* Substance;
extern Node* Synonym;
extern Node* Weight;
extern Node* Type;
extern Node* Instance;
extern Node* Active;
extern Node* Passive;
extern Node* Tag;
extern Node* Label;
extern Node* Labeled;
//extern Node* Labels;
//extern Node* LabeledNode;
extern Node* Comment;
extern Node* Description;

extern Node* Category;
extern Node* SubContext;
extern Node* SuperContext;
extern Node* Domain;
extern Node* Derived;
extern Node* UsageContext;
extern Node* PERTAINYM;

extern Node* Cause;
extern Node* Substance;

// Types
extern Node* Internal;
extern Node* _Node;
extern Node* Thing;
extern Node* Item;
extern Node* Abstract; // Thing
extern Node* Class;
extern Node* Entity; // == ?
extern Node* Object;
extern Node* Relation;
extern Node* Reification;
extern Node* Property;
extern Node* Pattern;// temporary

extern Node* Any;
// Semantics
extern Node* Attribute; //ok, if extern Node* Attribute declared in netbase.cpp
//extern Node* Is; // danger: obama is president etc

extern Node* Person;
extern Node* Adjective;
extern Node* Noun;
extern Node* Verb;
extern Node* Adverb;
extern Node* Number;
extern Node* String;
extern Node* Date;
extern Node* Float;
extern Node* Integer;
extern Node* Range;
extern Node* Unit;

extern Node* Bytes;// byte[] -> serialized java object etc etc
extern Node* Map; // Map<String,T>
extern Node* Array;// T[]
extern Node* List; // List<T>

extern Node* True;
extern Node* False;

extern Node* Translation;
extern Node* Plural;
extern Node* And;
extern Node* Or;
extern Node* Not;

//There are about 150 prepositions in English
extern Node* Of;// ==owner
extern Node* In;// ==location,...
extern Node* To;// ==direction,<object>
extern Node* From;
extern Node* By;
extern Node* For;
extern Node* On;


extern Node* Equals;
extern Node* Greater;
extern Node* Less; //smaller
extern Node* More;
extern Node* Smaller;
extern Node* Between;
extern Node* Circa;
extern Node* Much;
extern Node* Very;
extern Node* Contains;
extern Node* StartsWith;
extern Node* EndsWith;
extern Context* Wordnet;

// NEGATIVE VALUES GO IN PROPERTY_SLOTS!
// remove '-' if this scheme is detested

static const int propertyId = -98;
static const int singletonId = -99;
static const int abstractId = -102;

static const int wordnet = 0;// 303; //context==Class??   TODO!
static const int wikidata = 0;// for now
// DANGER!!
static const int _internal = -100;
static const int _node = -101;// dont change
static const int _abstract = -102;
//int Class=103;
static const int _klass = -103;
static const int _clazz = -103;
static const int _concept = -103;
static const int _object = -104;
static const int _entity = -104;
//int Object=104;
static const int _relation = -105;
static const int _person = -106;
static const int _reification=107;//== -_statement ??
static const int _pattern = -108;
static const int _statement = -109;

// wn: done via type(33) statements

static const int attribute = -42;
static const int noun = -110;
static const int verb = -111;
static const int adjective = -112;
static const int adverb = -113;
static const int preposition = -114;

static const int _bytes = -119;
static const int _map = -120;
static const int _array = -121;
static const int _list = -122;
static const int _number = -123;
static const int _integer = -124; //naa, see number
static const int _float = -125; //naa, see number
static const int _string = -126; // text
static const int _date = -127;
static const int unit = -128;
static const int _range = -129;

// syntactic relations:
static const int singular = -130;
static const int _plural = -131;
static const int present_tense = -132;
static const int past_tense = -133;
static const int future_tense = -134;
static const int translation = -139;

static const int _And = -140;
static const int _Or = -141;
static const int _Not = -142;
static const int _Equals = -150;
static const int _Greater = -151;
static const int _Less = -152;
static const int _Between = -153;
static const int _Circa = -154;
static const int _Much = -155;
static const int _Little = -165;
static const int _Very = -156;
static const int _Contains = -157;
static const int _StartsWith = -158;
static const int _EndsWith = -159;
static const int _false = -200;// not '0' by design!
static const int _true = -201;

static const int _error= -666;//-1 = -evil in itself;//
static const int _missing= -999;
static const int _any=0;// !!!
static const int _unknown=0;
static const int _see= -50,//50 also, -40 similar
	_Hypernym = -1,
	_SuperClass= -1,//SuperClass  bugs=>ARE=>animals
	_hyponym = -2,
	_SubClass= -2,//SubClass	animals=>i.e.=>bugs  (turn around!)
	_Type= -3,
	_instance= -4,
	_ENTAILMENT= -21,// implies
	_Part= -11,
	_PartOf= -12,
	_Member= -13,
	_Owner= -14,
	_Substance= -15,
	_SubstanceOwner= -16,
	_PARTICIPLE_OF_VERB= -71,
	_PERTAINYM= -80,
	_antonym= -30,
	_attribute= -60,
	_cause= -23,
	_derived= -81,
	_derived_from_noun=81,//?
	_synonym= -21, // 32
	_DOMAIN_CATEGORY= -91,
	_DOMAIN_REGION= -93,
	_DOMAIN_USAGE= -95,
	_MEMBER_DOMAIN_CATEGORY= -92,
	_MEMBER_DOMAIN_REGION= -94,
	_MEMBER_DOMAIN_USAGE= -96,
_VERB_GROUP= -70;
// Wordnet:
//static const int	_antonym= -1,
//	_attribute= -2,
//	_cause= -3,
//	_derived= -4,
//	_derived_from_noun= -5,
//	_DOMAIN_CATEGORY= -6,
//	_DOMAIN_REGION= -7,
//	_DOMAIN_USAGE= -8,
//	_ENTAILMENT= -9,// implies
//	_Hypernym= -10,//SuperClass
//	_hyponym= -11,//SubClass
//	_Owner= -12,
//	_Member= -13,
//	_MEMBER_DOMAIN_CATEGORY= -14,
//	_MEMBER_DOMAIN_REGION= -15,
//	_MEMBER_DOMAIN_USAGE= -16,
//	_PartOf= -17,
//	_Part= -18,
//	_PARTICIPLE_OF_VERB= -19,
//	_PERTAINYM= -20,
//	_synonym= -21,//32?
//	_SubstanceOwner= -22,
//	_Substance= -23,
//	_VERB_GROUP= -24,
//	_Type= -33,
//_instance= -34;

static const int // additional
_DOMAIN= -97,
_DOMAIN_MEMBER= -98,
_weight = -31,
_active = -35,
_passive = -36,
_tag = -37, // = ?
_label = -38,
_labeled = -39,
_similar = -40,
_see_also = -50,
_category = -43,
_subcontext = -44,
_supercontext = -45,
_comment = -46,
_description = -49;


void initRelations();
Node * getRelation(const char* thing);
Node* invert(Node* relation);
#endif	/* RELATIONS_HPP */

