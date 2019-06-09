
# Matter Code Style

## Sections

- Code Style Choices
  - Intendation
  - Curly Brackets
  - Pointers
- Documentation
  - Variables
  - Functions
  - Classes

## Code Style Choices

### Intendation

All lines are indented with 4 spaces (not a single tab).

### Curly Brackets

Curly brackets sit on a line by themselves:

```
if (age >= 18)
{

}
else if (age >= 13)
{

}
else
{

}
```

This applies to classes as well:

```
class Cat
{

}
```

### Pointers

The `*` of a pointer sits a space after the type, e.g. `char *name` or `Point *`.

## Documentation

Documentation comments are strict as a document generator will be used. We are aiming for full coverage.

### Comment Syntax

- Single line comments (e.g. variables) use `///`.
- Multi-line comments (e.g. functions with parameters) use the following syntax:

```
/**
 * Multi-line
 * Comment
 */
```

#### Types

- `@param` refers to a function parameter, it is followed by the parameter name and a description, e.g. `@param <name> <description>`.
- `@return` refers to what a function returns, it only needs to be followed with a description, e.g. `@return <description>`.
If there is no return value then it can be ommited.

### Variables

Variables only require a description:

```
/// Age of the person
int age = 18
```

### Functions

Functions require all parameters and what it returns to be documented, this uses `@param` and `@return`. `@param`s should be on a new line below each other and `@return` should be seperated by `@param` by an empty line.

If the function has no parameters then `@param` can be ommited. As can `@return` if the function doesn't return a value.

```
/**
 * Add two numbers together.
 * 
 * @param x First number
 * @param y Second number
 *
 * @return Product of the two numbers
 */
int add(int x, int y)
{
    return x + y;
}
```

### Classes

Classes always require a description regardless of if they have a constructor or not. If they do have a constructor then they should follow the function documentation omitting `@return`.

```
/**
 * Used to represent a person.
 *
 * @param name Name of the person
 * @param age Age of the person
 */
class Person
{
public:
    int age;
    char *name;

    Person(int, char *);
 };

Person::Person(int age, char *name)
{
    this->age = age;
    this->name = name;
}
```

