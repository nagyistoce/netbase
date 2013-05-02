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
extern Node* Substance;
extern Node* Synonym;
extern Node* Weight;
extern Node* Type;
extern Node* Instance;
extern Node* Active;
extern Node* Passive;
extern Node* Tag;
extern Node* Label;
extern Node* BackLabel;
extern Node* Labels;
extern Node* LabeledNode;
extern Node* Category;
extern Node* SubContext;
extern Node* SuperContext;

// Types
extern Node* Internal;
extern Node* _Node;
extern Node* Thing;
extern Node* Item;
extern Node* Abstract; // Thing
extern Node* Class;
extern Node* Object;
extern Node* Relation;
extern Node* Reification;
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
extern Node* Unit;

extern Node* Cause;
extern Node* Substance;

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
extern Node* Between;
extern Node* Circa;
extern Node* Much;
extern Node* Very;
extern Node* Contains;
extern Node* StartsWith;
extern Node* EndsWith;
extern Context* Wordnet;

static const int abstractId = 102;


static const int wordnet = 303; //context==Class??   TODO!
// DANGER!!
static const int _internal = 100;
static const int _node = 101;// dont change
static const int _abstract = 102;
//int Class=103;
static const int _klass = 103;
static const int _clazz = 103;
static const int _concept = 103;
static const int _object = 104;
//int Object=104;
static const int _relation = 105;
static const int _person = 106;
static const int _reification=107;
static const int _pattern = 108;
static const int _statement = 109;

// wn: done via type(33) statements

static const int attribute = 42;
static const int noun = 110;
static const int verb = 111;
static const int adjective = 112;
static const int adverb = 113;
static const int number = 123;
static const int _string = 124; // text
static const int _float = 125; //naa, see number
static const int _integer = 126; //naa, see number
static const int _date = 127;
static const int unit = 128;
static const int _range = 129;

// syntactic relations:
static const int singular = 130;
static const int plural = 131;
static const int present_tense = 132;
static const int past_tense = 133;
static const int future_tense = 134;
static const int translation = 139;

static const int _And = 140;
static const int _Or = 141;
static const int _Not = 142;
static const int _Equals = 150;
static const int _Greater = 151;
static const int _Less = 152;
static const int _Between = 153;
static const int _Circa = 154;
static const int _Much = 155;
static const int _Very = 156;
static const int _Contains = 157;
static const int _StartsWith = 158;
static const int _EndsWith = 159;


void initRelations();
#endif	/* RELATIONS_HPP */
