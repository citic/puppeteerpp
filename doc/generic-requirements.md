Generic requirements
====================

The requierements listed in this document are generic for any video game or game-based solution intended to help students to learn **any** programming language.



System attributes
-----------------

### Game based

The system must be one of the following:

* A videogame
* A system to make new games
* A game engine
* A visualization tool


### Learning of a programming language

The system must be designed for teaching or learning a specific programming language. Therefore, commercial game engines are not suitable for this system.


### Multi-platform support

Students and professors have a plethora of choices for operating systems and devices. The more systems supported, the more likely it would be used for both of them.



Functional requirements
-----------------------

### Language coverage

Software must cover full range of features of the programming language, or a least the most important topics for a programming course. For example, for C++ these topics could be:

* Memory management
* Classes and instances
* Operator overloading
* Templates
* Inheritance and polymorphism


### Incremental learning

The software must allow students to create simple programs and complex programs. Ability of creating simple programs is required to be usable in the first weeks of a programming course, complex programs are required by the end of the course, when students work with projects.


### Encourage creativity

System should support a constructivist or constructionist method of learning for the students. Therefore, students should be able to ideate new creations and implement them with the provided system.


### Build documentation from source

The system must encourage students to document code. It should provide mechanisms for easily building documentation from comments (e.g. Doxygen, Javadoc), consult the generated documentation, and suggesting user to write comments.

For example, each time user creates a function or method, a Doxygen comment should be automatically provided with placeholders for parameters, return value, and so on. Autocompletion is welcome.


### Code reuse

System should encourage code reuse, mainly for standard libraries of the programming language. That is, the system should face student with necessity of requiring functionality that is implemented by other people. For example, containers, network or database support.


### Illustrate memory segments

The system should make clear the difference between the four segments of any running program: code segment, data segment (static memory), stack segment, heap segment (dynamic memory).

Ideally this difference should be visually represented, because it is hidden for the student when programming and running applications.

The system should allow user to associate how each memory segment is managed by the programming language.


### Visual debugging

The system should allow user to run a program step by step and show the effect of each instruction in visual way. This let user to get a visual representation of the hidden internals of a typical program.

Other typical functionality of debuggers is also desired.


### Code production assistant

The system should help user to write valid code and apply good programming principles. For example, the system should provide code completion, hints for common problems (syntactic and logical), and other functionality that helps the student to realize when writing some erroneous code.


### Encourage team work

The system should encourage collaborative work. For example: collaboration is mandatory to pass some levels.


### Allow building large projects

The system should allow students to build large projects, in order to support a constructivist technique called project based learning (PBL).
