```
 ____   ___  ____ _____  _    ____ _  ______  _   _ _____ _____ _____ ____
|  _ \ / _ \/ ___|_   _|/ \  / ___| |/ / __ )| | | |  ___|  ___| ____|  _ \
| | | | | | \___ \ | | / _ \| |   | ' /|  _ \| | | | |_  | |_  |  _| | |_) |
| |_| | |_| |___) || |/ ___ \ |___| . \| |_) | |_| |  _| |  _| | |___|  _ <
|____/ \___/|____/ |_/_/   \_\____|_|\_\____/ \___/|_|   |_|   |_____|_| \_\
  _____     _______ ____  _____ _     _____        ______  ___   ___  ____
 / _ \ \   / / ____|  _ \|  ___| |   / _ \ \      / / ___|/ _ \ / _ \|  _ \
| | | \ \ / /|  _| | |_) | |_  | |  | | | \ \ /\ / / |  _| | | | | | | | | |
| |_| |\ V / | |___|  _ <|  _| | |__| |_| |\ V  V /| |_| | |_| | |_| | |_| |
 \___/  \_/  |_____|_| \_\_|   |_____\___/  \_/\_/  \____|\___/ \___/|____/
```

Created for CrikeyCon 3, 20 February 2016

## tl; dr

If you're in a hurry, you're almost certainly looking for the following resources:

* [`dostackbufferoverflowgood.exe`](/dostackbufferoverflowgood.exe) - an intentionally vulnerable Windows program
* [`dostackbufferoveflowgood_tutorial.pdf`](/dostackbufferoverflowgood_tutorial.pdf) - A PDF tutorial that explains how to exploit the above program

## A brief history

The resources in this repo were created for a talk at
[Crikeycon](https://www.crikeycon.com) in 2016. A recording of that talk is
available at <https://www.youtube.com/watch?v=renR0Aj2YzI>.

## How you can support me

Please share these resources with your friends. They are freely licensed, so
you are even welcome to present them at your local hacker meetup or in your
company. All I ask is that you credit me as the original author.

You can [Follow me on Twitter](https://twitter.com/justinsteven) and let me
know that you popped calc.

If you want to see more of my content, please subscribe to my [Youtube
channel](https://youtube.com/justinsteven) and follow me on
[Twitch](https://twitch.tv/justinsteven)

Finally, if these resources brought you joy or helped you on your journey to
OSCP and you would feel awesome about supporting me financially, you can buy
me a coffee. If it wouldn't make you feel awesome, please don't feel obliged.
This content will always be 100% free for you to enjoy, modify and distribute
:heart:

<a href='https://ko-fi.com/K3K51B01A' target='_blank'>
  <img height='36' style='border:0px;height:36px;' src='https://az743702.vo.msecnd.net/cdn/kofi4.png?v=2' border='0' alt='Buy Me a Coffee at ko-fi.com' />
</a>

## Abstract

Did you miss out on stack-smashing for enjoyment and financial gain? Have you
always meant to get in to "all that debugger stuff" but don't know your EIP
from your ESP? Let's take it back to the 90s for an overview of Win32 stack
buffer overflow exploitation.

We'll cover assembly, registers, the stack, function call and return mechanics,
triggering stack buffer overflows, taking advantage of saved return pointer
overwrites, generating shellcode, and some other weird tricks.

This is not new stuff, and modern mitigations (ASLR, DEP and stack canaries)
totally harsh its mellow. If you're a stack savant who has a handle on the
heap and ROPs relentlessly then this content isn't for you. For everyone
else, may you learn to pop calc not alert(1)

## Contents of this repo

* [`dostackbufferoverflowgood.exe`](/dostackbufferoverflowgood.exe) - Intentionally vulnerable binary. Compiled without ASLR, DEP or Stack Canaries.
* [`dostackbufferoverflowgood_tutorial.pdf`](/dostackbufferoverflowgood_tutorial.pdf) - A tutorial for the above binary
* [`dostackbufferoverflowgood_slides.pdf`](/dostackbufferoverflowgood_slides.pdf) - Presentation slides
* [`dostackbufferoverflowgood`](/dostackbufferoverflowgood) - **Optional** Visual Studio solution for `dostackbufferoverflow.exe`
* [`dostackbufferoverflowgood.pdb`](/dostackbufferoverflowgood.pdb) - **Optional** Debug symbols for `dostackbufferoverflowgood.exe`

## License

The code for `dostackbufferoverflowgood.exe` is licensed under Apache License
Version 2.0

The slides and tutorial are licensed under a Creative Commons Attribution 4.0
International License.

You are welcome to modify and redistribute this material, provided you credit
me as the original author.
