# CSE_4302_Project
--------------------

| Name                    | ID        |
|-------------------------|-----------|
| Najmus Sakib            | 230041149 |
| Aahil Zaman             | 230041133 |
| Md. Azizul Hakim Khan   | 230041141 |
| Sami Rahman             | 230041111 |


# School Management System
----------------------------


### Common things to remember
 - Use src folder for storing source .cpp files
 - Follow [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) when writing commit messages

 - Don't setup build directory over and over again. [See more](https://github.com/Afsan-z47/CSE_4302_Project#compile-and-run-meson) here at Build the project

### Compile and Run (Meson)
1. **Install Meson and Ninja** (if not installed):

- **Fedora / RedHat**:
```bash
sudo dnf install meson ninja-build
```
 - **Ubuntu / Debian**:

```bash
sudo apt update
sudo apt install meson ninja-build
```
 - **macOS (using Homebrew)**:

```bash
brew install meson ninja
```

2. **Set up build directory**:

```bash
meson setup build
```

3. **Build the project**:

> [!NOTE]
> Start from this part if you already have a set up build directory. No need to reinstall and setup build directory over and over again.

```bash
meson compile -C build
```

4. **Run the executable**:

```bash
./build/project.o
```

### Configuring meson.build / How to add more files to compile
  - At ***the CSE_4302_Project/src*** directory edit ***meson.build*** file.
  - You should see something like this...

```meson
# src file list

sources = files(
	'main.cpp'
#       'other.cpp'  # add other files like this. 
	             # Besure to add commas (,) to previous ones ends.
)

# Build an executable

executable('project.o', sources)
```
   - As directed, add your new file below the main.cpp in the appropriate format.

---

### TODO

- [ ] Better README
- [ ] Initial Codes
- [x] Configure make file -> Used meson as a build system
- [ ] Configure .gitignore
- [ ] Integrate Clang-tidy

### Coding Standards

* [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html)
* [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
