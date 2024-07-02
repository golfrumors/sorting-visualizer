## Getting Started
Once the project is compiled and the binary is ran, one can start/pause the sort by pressing space.
Once the sorting complete, or interrupted, one can regenerate and reshuffle the array by pressing r.

### Prerequisites
* This piece of code depends on the [SFML](https://www.sfml-dev.org/) libraries, in particular their graphics and audio components.
* It also depends on [CMake](https://cmake.org/) to compile and build.

### Compiling
1. Clone the repo
```sh
git clone https://github.com/golfrumors/sorting-visualizer
```
2. Cd into the appropriate folder
```sh
cd sorting-visualizer
```
3. Tweak settings as needed
4. In the root directory, create a new folder to hold the executable
```sh
mkdir build && cd build
```
5. Compile the project using CMake
```sh
cmake .. && cmake --build .
```
6. Run the executable
```sh
./SortingVisualizer
```

## TODO List
- [ ] Add delays to individual sorting aglorithms
- [ ] Make the access & comparisons text look better
- [x] Implement Merge Sort
- [x] Implement Heap Sort
- [x] Implement Counting Sort
- [x] Implement Radix Sort
- [x] Implement Bucket Sort
- [ ] Implement Bingo Sort Algorithm
- [x] Implement ShellSort
- [x] Implement TimSort
- [ ] Implement Comb Sort
- [ ] Implement Pigeonhole Sort
- [ ] Implement Cycle Sort
- [ ] Implement Cocktail Sort
- [ ] Implement Strand Sort
- [ ] Implement Bitonic Sort
- [ ] Implement Pancake sorting
- [ ] Implement BogoSort or Permutation Sort
- [ ] Implement Gnome Sort
- [ ] Implement Sleep Sort – The King of Laziness
- [ ] Implement Structure Sorting in C++
- [ ] Implement Stooge Sort
- [ ] Implement Tag Sort (To get both sorted and original)
- [ ] Implement Tree Sort
- [ ] Implement Odd-Even Sort / Brick Sort
- [ ] Implement 3-way Merge Sort
