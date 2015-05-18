#Hungarian notation


##Purpose

The purpose of this article is to take a look at some of the most [influential techniques of naming](http://en.wikipedia.org/wiki/Naming_convention_(programming)), along with a brief history of it's origins and it's [creator](http://en.wikipedia.org/wiki/Charles_Simonyi). In addition to these, examples will be demonstrated to help understand the pros and cons behind this particular notation.

##Objectives

* _Presentation of **Charles Simonyi**_
* _Notation analysis_
* _A few examples_
* _Review advantages & disadvantages_

---

##Table of contents

* [Origins](#origins)
* [Notation](#notation)
* [Examples](#examples)
* [Advantages](#advantages) & 
[disadvantages](#disadvantages)
* [Links](#links)

---

##Origins

The the early days of [programming](http://en.wikipedia.org/wiki/Computer_programming), there were no such things as [intellisense](http://en.wikipedia.org/wiki/Intelligent_code_completion) or [code completion](http://en.wikipedia.org/wiki/Autocomplete#In_source_code_editors) features-like in compilers. Unlike today's [IDEs](http://en.wikipedia.org/wiki/Integrated_development_environment), [source code editors](http://en.wikipedia.org/wiki/Source_code_editor) used to look more or less of regular [text editors](http://en.wikipedia.org/wiki/Notepad_%28software%29). As software programs were getting more complex, code had to be separated in multiple source files, thus obligating programmers to review already defined [instructions](http://en.wikipedia.org/wiki/Instruction_set) before writing new ones.

In 1981, [Charles Simonyi](http://en.wikipedia.org/wiki/Charles_Simonyi), a programmer, was hired by [Microsoft](http://en.wikipedia.org/wiki/Microsoft) to work on several tools. He also introduced the principles of [Object-oriented programming](http://en.wikipedia.org/wiki/Object-oriented_programming), as well as formal technique for naming variables, which is still widely used today by the company, [Hungarian notation](http://en.wikipedia.org/wiki/Hungarian_notation).

The purpose of this notation is to [prefix](http://en.wikipedia.org/wiki/Prefix) the name of [variables](http://en.wikipedia.org/wiki/Variable_(computer_science)) with their corresponding [data type](http://en.wikipedia.org/wiki/Data_type), thus making it easier to deduce their [physical representation](http://en.wikipedia.org/wiki/Hungarian_notation#Systems_vs._Apps_Hungarian).


##Notation

For a quick refresh, here is a list of [fundamental types](http://en.cppreference.com/w/cpp/language/types)

---

```cpp
bool
char
signed char
unsigned char
short
signed short
unsigned short
int signed int
unsigned int
long
signed long
unsigned long
float
double
```

---

###Variables

The hungarian notation can be applied by prefixing the name of each variable.

Here is a list of defined convention for literals for prefixes. This is **not** a complete table, as it  only essential concepts are covered to ease understanding. For a more complete table, readers should refer to [this page](http://web.mst.edu/~cpp/common/hungarian.html).

|Prefix|Type|
|:--|:--|
|`b`| [boolean](http://en.wikipedia.org/wiki/Boolean_data_type)/[byte](http://en.wikipedia.org/wiki/Byte)|
|`c`, `ch`|[character](http://en.wikipedia.org/wiki/Character_%28computing%29)|
|`str`, `sz`| [null terminated string](http://en.wikipedia.org/wiki/Null-terminated_string)|
|`si`|[short integer](http://en.wikipedia.org/wiki/Integer_(computer_science)#Short_integer)|
|`i`|[integer](http://en.wikipedia.org/wiki/Integer_(computer_science))|
|`li`|[long integer](http://en.wikipedia.org/wiki/Integer_(computer_science)#Long_integer)|
|`l`|[long](http://en.wikipedia.org/wiki/Integer_%28computer_science%29#Long_integer)|
|`ll`|[long long](http://en.wikipedia.org/wiki/Integer_(computer_science)#Long_integer)|
|`f`|[single-precision floating point](http://en.wikipedia.org/wiki/Single-precision_floating-point_format).|
|`d`|[double-precision floating point](http://en.wikipedia.org/wiki/Double-precision_floating-point_format).|
|`ld`|[quadruple-precision floating point](http://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format).|

######Additional letters before prefixes

[Prefixes](http://en.wikipedia.org/wiki/Prefix) can, themselves, be prefixed as well. 
These prefix predecessors, most commonly called pre-prefixes are mostly used to give a clue of the general characteristics whose associated variable have in the source code, such as: [pointer](http://en.wikipedia.org/wiki/Pointer_%28computer_programming%29), [reference](http://en.wikipedia.org/wiki/Reference_%28computer_science%29), [scope](http://en.wikipedia.org/wiki/Scope_%28computer_science%29), [capacity](http://en.wikipedia.org/wiki/Dynamic_array#Bounded-size_dynamic_arrays_and_capacity).

|Pre-prefix|Description|
|:--|:--|
|`k`|a constant or [immutable](http://en.wikipedia.org/wiki/Immutable_object) variable.|
|`u`|[unsigned](http://en.wikipedia.org/wiki/Signedness) variable.|
|`p`|A pointer to a variable.|
|`g`|Global variable.|
|`m_`|member variable from class or struct.|
|`s`|A static variable|

###Classes & Data structures

|Prefix|Type|
|:-|:-|
|`S`|struct|
|`C`|class|

##Examples

####1. With an integer

Let `count` be  an integer variable with data type `int`.

**Regular notation**
```cpp
int count = 0;
```
**Hungarian notation**
```cpp
int iCount = 0;
```

Notice how the first letter of `count`, **_c_**, has been made [upper case](http://en.wikipedia.org/wiki/Letter_case). This is usually a good practice, as it follows the [lowerCamelCase](http://en.wikipedia.org/wiki/CamelCase) writing convention that is adopted by many of today's standards employed for [clarity](http://en.wikipedia.org/wiki/Naming_convention_(programming)), [readability](http://en.wikipedia.org/wiki/Naming_convention_(programming))

####2. With a string

Let `guid` be a `string`.

**Regular notation**
```cpp
char[] guid = "7CD7BFED-AB28-467B-867A-18B9A1C97F7D";
```
**Hungarian notation**
```cpp
char[] strGuid = "7CD7BFED-AB28-467B-867A-18B9A1C97F7D";
//     szGuid can also be used.
```


####Other examples

**Hungarian notation**
```cpp
float        fScale;     // f -> float

double       dDistance;  // d -> double

bool         bIsReady;   // b -> bool/byte

char         chLetter;   // ch -> char

const char*  pszText;    // p -> pointer     
                         // sz-> string

unsigned int uiSize;     // u -> unsigned
                         // i -> int

static const char* spstrArray[12]; // s -> static
                                   // p -> pointer
                                   // str -> string

void foo( const int kiMaxCount );  // k -> const 
                                   // i -> int

void bar( int& rOut ); // r -> reference

```

For more advantages & disadvantages, readers should refer to this [page](http://en.wikipedia.org/wiki/Hungarian_notation#Advantages).

##Advantages

* The type of the variable is explicitly stated, eliminating the need to check [declaration](http://en.wikipedia.org/wiki/Declaration_(computer_programming)).
* invalid [type casting](http://en.wikipedia.org/wiki/Type_conversion) and [logic errors](http://en.wikipedia.org/wiki/Logic_error) are easier to spot when reading code.
* If multiple conversions are necessary for a single operation, similar [semantics](http://en.wikipedia.org/wiki/Semantics_%28computer_science%29) can be used on multiple variables

##Disadvantages

* Redunctant, due to modern [code completion](http://en.wikipedia.org/wiki/Intelligent_code_completion) in many [IDEs](http://en.wikipedia.org/wiki/Integrated_development_environment).
* Can lead to confusion as variable data types can be altered by other programmers.
* Since data type is evaluation at [compile time](http://en.wikipedia.org/wiki/Compile_time) by the compiler, consistency is inevitable unlike human eye verification, which is prone to errors

##Links

|Reference|Link|
|:--|:--|
|Advantages \& Disadvantages|[Wikipedia](http://en.wikipedia.org/wiki/Hungarian_notation)|
|Pre-prefixes|[web.mst.edu](http://web.mst.edu/~cpp/common/hungarian.html)|
