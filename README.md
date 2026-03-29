<!-- Optional.h - Macro-based Option Type for C -->

<div align="center">

# 🧩 C Optional Macro

**A simple, header‑only, macro‑based implementation of the `Option` type for C.**  
*Inspired by Rust’s `Option` and functional programming patterns.*

[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Header‑only](https://img.shields.io/badge/Header‑only-brightgreen.svg)](https://en.wikipedia.org/wiki/Header-only)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

---

## 📖 Overview

This project provides a single macro – **`DEFINE_OPTION(NAME, TYPE)`** – that generates a complete `Option`‑like type for any given C type.  
It mimics the behaviour of `Option<T>` in Rust or `std::optional` in C++17, but without any external dependencies.

The generated type is a tagged union with two variants:
- `NAME_None` (empty)
- `NAME_Some` (contains a value of `TYPE`)

All operations are implemented as `static inline` functions, so there is **no runtime overhead** – the compiler inlines everything.

---

## ✨ Features

- **Header‑only** – just `#include "Optional.h"` and you’re ready.
- **Works with any type** – primitives, structs, pointers, etc.
- **Safe by design** – functions like `is_some` let you check the state before unwrapping.
- **Zero overhead** – all functions are `static inline`, producing code as efficient as manual checks.
- **Simple API** – similar to Rust’s `Option` methods.

---

## 🚀 Usage

1. Include the header in your source file:
   ```c
   #include "Optional.h"
   ```
2. Define a conrete option functionality for your type:
   ```c
   DEFINE_OPTION(IntOption, int);       // Creates IntOption for int
   DEFINE_OPTION(StringOption, char*);   // Creates StringOption for char*
   DEFINE_OPTION(MyStructOption, MyStruct); // For any struct
   ```
3. Use the generated functions:
   ```c
   IntOption some = IntOption_some(42);
   IntOption none = IntOption_none();

   if (IntOption_is_some(&some)) {
     printf("Value: %d\n", IntOption_unwrap(&some));
   }
   ```

---

## 📦 Generated API

When you type ``` DEFINE_OPTION(NAME, TYPE) ``` the macro generates the following types and functions:
|          **Entity**          |          **Description**          |
|:-----------------------------|-----------------------------------|
|         ```NAME```           |  The struct that represents an option. Contains a ```tag``` and a ```union```.|
|              ```NAME##_Tag```| Enum: ```NAME##_Some``` and ```NAME##_None```.|
| ```NAME##_some(TYPE value)```| Creates an option type with given value. |
|  ```NAME##_none()```         |  Creates an empty option type. |
|  ```NAME##_is_some(NAME* opt)```      | Returns ```1``` if the value exists, ```0``` otherwise.|
|   ```NAME##_unwrap(NAME* opt)```   |    Extracts the contained value **without checking!**. Unsafe if ```None```!   |
| ```NAME##_unwrap_or(NAME* opt, TYPE* default_value)``` |   Returns the contained data or default value if empty.   |
|  ```NAME##_take(NAME* opt)``` | Takes the value out of the option type, leaving it as ```None``` |

> ⚠️**Caution:**```unwrap()``` **does not** check the option tag. Always use ```is_some()``` at first, or use ```unwrap_or()``` or ```take()``` when appropriate. Also be be cautios when working with allocated memory and ```take()``` function as it is zeroing the contained memory after being taken.

---

## Example

```c
#include "Optional.h"
#include <stdio.h>

DEFINE_OPTION(IntOption, int);

void print_option(IntOption* opt) {
    if (IntOption_is_some(opt)) {
        int val = IntOption_unwrap(opt);
        printf("Some(%d)\n", val);
    } else {
        printf("None\n");
    }
}

int main() {
    IntOption a = IntOption_some(42);
    IntOption b = IntOption_none();

    print_option(&a);  // Some(42)
    print_option(&b);  // None

    // Using unwrap_or
    int fallback = 0;
    printf("a unwrap_or: %d\n", IntOption_unwrap_or(&a, &fallback)); // 42
    printf("b unwrap_or: %d\n", IntOption_unwrap_or(&b, &fallback)); // 0

    // Take value from a, leaving it empty
    int taken = IntOption_take(&a);
    printf("Taken: %d\n", taken);    // 42
    print_option(&a);                // None

    return 0;
}
```

---

## 🔧 How it works

### The macro expands to:

```c
typedef enum { NAME_None, NAME_Some } NAME_Tag;

typedef struct {
    NAME_Tag tag;
    union {
        TYPE some;
    } data;
} NAME;

static inline NAME NAME_some(TYPE value) { ... }
static inline NAME NAME_none() { ... }
static inline int NAME_is_some(NAME* opt) { ... }
static inline TYPE NAME_unwrap(NAME* opt) { ... }
static inline TYPE NAME_unwrap_or(NAME* opt, TYPE* default_value) { ... }
static inline TYPE NAME_take(NAME* opt) { ... }
```

---

## LICENSE

This project is licensed under the MIT License.
See the [LICENSE](https://github.com/terra-fx-t-byte/C-Optional/blob/main/LICENSE) file for details.

---

<div align="center"> Made with ❤️ for C programmers who miss their Option types. </div>


