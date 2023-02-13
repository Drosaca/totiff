# ToTiff

---

 Tool to convert images from __img_rgb__ to tiff format

## Usage

---

```shell
./totiff /path/to/image.ims_rgb <width> <height>
```
_note: As the file format does not inform about the image size It has to be provided to the converter as arguments._

## Build

---

### Dependencies
- Ninja (Optional: When using preset)
- cmake (v3.22+)

Linux
- libtiff-dev (Ubuntu)

Windows
- libtiff (included in deps/windows)

### Build Using Preset

```shell
cmake --preset default
cmake --build --preset default
```

### Build Without Preset

```shell
mkdir build && cd build
cmake ..
cmake --build .
```


## Binaries

---
### Windows
Extract the zip file and keep the dll file with it.

### Linux
Binary file is standalone as libtiff is installed by default on Ubuntu.