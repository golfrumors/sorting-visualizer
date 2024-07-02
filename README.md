### Prerequisites
* This piece of code depends on the [SFML](https://www.sfml-dev.org/) libraries, in particular their graphics and audio components.
* It depends as well on [CMake](https://cmake.org/) for the build.

### Compiling
1. Clone the repo
```sh
git clone https://github.com/golfrumors/sorting-visualizer
```
2. Tweak settings as needed
3. In the root directory, create a new folder to hold the executable
```sh
mkdir build && cd build
```
4. Compile the project using CMake
```sh
cmake .. && cmake --build .
```
5. Run the executable
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
- [ ] Implement ShellSort
- [ ] Implement TimSort
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
