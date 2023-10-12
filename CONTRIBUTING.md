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

# OGxx directories

* __include__ for public interfaces declared in .hpp files;
* __source__ for all implementation (.hpp and .cpp files);
* __tests__ for regression tests;
* __samples__ for sample applications.
