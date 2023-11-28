# OGxx generic rules

1. Each collaborator is to be given a separate branch and assigned tasks through the issues system.
2. There are several possible activities:
   * writing code;
   * writing tests;
   * documenting the code;
   * reviewing code.

# OGxx code style

1. Snake case naming:
   * Some_type_name;
   * some_variable_or_function_name;
   * some_constant_or_enum_item_name.
2. Tabs/spaces, indentation, braces, (CR)LF — as you wish, but neat and consistent across your code.
3. UTF-8 encoding only.
4. Documentation style: [Doxygen](https://www.doxygen.nl/index.html).
5. Testing library: [doctest](https://github.com/doctest/doctest).
6. Header files must have .hpp extension, translation units must have .cpp extension.
7. Header file header.hpp should have OGXX_HEADER_HPP_INCLUDED include guard.
8. The first three lines in each C++ code file must be a documenting comment of the following form:

```cpp
/// @file filename
/// @brief Description of the file contents.
/// @author Surname N.P.
```

# OGxx directories

* __include__/__ogxx__ for public interfaces declared in .hpp files;
* __source__ for all implementation (.hpp and .cpp files);
* __tests__ for regression tests;
* __samples__ for sample applications.

# OGxx code decisions

1. Use references (better) or primitive pointers (when references can not be used) to provide access but not ownership. Use unique_ptr to hand over ownership (e.g. fabric methods should return unique_ptr).
2. No special read-only interfaces. An implementation class may be read-only, then it shall implement modifiers as no-op or throwing stubs. Such objects must be returned by a const-reference or a pointer to a constant, casting its constness away implies undefined behaviour in general case.
3. We have two inheritance hierarchies: that of no-data abstract base classes (interfaces) and that of implementation classes. Interfaces should use virtual inheritance for more robust results.
