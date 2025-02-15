# UniversalRemote

Universal Remote is a universal remote control project based on M5Cardputer, featuring an IR transmitter to manage various TV brands. It lets you switch TV brands on the fly and send essential commands like volume, channel changes, and menu navigation.

![](https://github.com/Alexxdal/UniversalRemote/blob/main/images/UniversalRemote.png?raw=true)

## Installation

Use [PlatformIO](https://platformio.org/) to install the dependencies and flash the firmware onto your M5Cardputer. 

#### 1. Clone the Repository

```bash
git clone https://github.com/Alexxdal/UniversalRemote.git
cd UniversalRemote
```

#### 2. Install the Required Libraries

Your platformio.ini should look like this
```c
[env:m5stack-stamps3]
platform = espressif32
board = m5stack-stamps3
framework = arduino
lib_deps = 
    m5stack/M5Cardputer@^1.0.3
    z3t0/IRremote@^4.4.1
```

#### 3. Upload to M5Cardputer

Open the project in PlatformIO, then build and upload the code to your device.

## Flash the firmware

If you dont want to compile it yourself you can download the release bin file and place it on an SD Card and use this [M5Stick-Launcher](https://bmorcelli.github.io/M5Stick-Launcher/) to load the firmware.

## Usage

### 1. Select the Brand:

- Press the `FN` key to cycle through available TV brands.

### 2. Send IR Commands:

- Press `TAB` to send `POWER`
- Press `S` and `Z` to send Volume Up and Volume Down
- Press `F` and `C` to send Channel Up and Channel Down
- Press `ENTER` for `OK` and Arrows
- Press `SPACE` for `HOME` and `DEL` for `EXIT`
- Press `M` for `MENU`
- Press number to send them

## Supported Brands

| Brand            |  Protocol          | Bits  |
|:-----------------|:------------------:|------:|
| **Samsung**      |  NEC               | 32    |
| **LG**           |  LG Proprietary    | 28    |
| **Philips**      |  RC5/RC6           | 12/20 |
| **Sony**         |  SIRC              | 12    |
| **Panasonic**    |  Kaseikyo          | 48    |
| **Sharp**        | Sharp Proprietary  | 15    |
| **Telefunken**   | NEC                | 32    |
| **Hisense**      | NEC                | 32    |

Some unlisted brands are compatible with protocols above.


## Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)# Universal Remote
