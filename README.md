# Serial Pixel

Ardunio library for controlling NeoPixel LEDs over serial.

Load onto your favorite arduindo and then control your pixels via serial.

## Commands

Commands have the following form:

| CTL | Payload | END |
|-----|---------|-----|
| 1 byte | 0..N bytes | '\n' |

### Init Command

Either one of:

| CTL | N | END |
|-----|---|-----|
| 'I' | 2 bytes | '\n' |

or

| CTL | N | C | END |
|-----|---|---|-----|
| 'I' | 2 bytes | 2 bytes | '\n' |

* N represents the number of pixels in hex (ie, 26 pixels is `1a`)
* C (optional) are the config bytes in hex. 
  * This is not necessary when your neopixel is `GRB`, but is for all other pixel types.

### RGB Command

| CTL | INDEX | RGB[0..N] | END  |
|-----|-------|-----------|------|
| 'S' | 2 bytes | 6xN bytes | '\n' |

* INDEX represents the start LED index
* RGB[0..N] are 3-byte multiples of RGB values to apply to sequential LEDs.

### HSV Command

| CTL | INDEX | HSV[0..N] | END  |
|-----|-------|-----------|------|
| 'S' | 2 bytes | 6xN bytes | '\n' |

* INDEX represents the start LED index
* HSV[0..N] are 3-byte multiples of HSV values to apply to sequential LEDs.

### Show Command

| CTL | END  |
|-----|------|
| 'S' | '\n' |

Applies updates to the LEDs... without calling this, the other commands have not affect on your LEDs.

### Clear Command

| CTL | END  |
|-----|------|
| 'C' | '\n' |

Clears all pixels. Send a `Show` command to update the LEDs.

## Example

The following example sets up a strip of 6 LEDs and sets them to red

```
I06
R00ff0000ff0000ff0000ff0000ff0000ff0000
S
```

The following applies HSV to show colors across the color spectrum
```
I06
H0000ffff20ffff40ffff60ffff80ffffa0ffff
S
```

