
#!/usr/bin/env python3
from pathlib import Path
import sys, os
from PIL import Image, ImageSequence

ALPHA_KEY = 0xF81F

def rgb565(r, g, b):
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)

def flatten(img, maxw, maxh, allow_resize=True):
    img = img.convert('RGBA')
    w0, h0 = img.size
    if allow_resize and (w0, h0) != (maxw, maxh):
        img.thumbnail((maxw, maxh), Image.NEAREST)
    w, h = img.size
    px = img.load()
    data = []
    for y in range(h):
        for x in range(w):
            r, g, b, a = px[x, y]
            if a < 128:
                data.append(ALPHA_KEY)
            else:
                v = rgb565(r, g, b)
                if v == ALPHA_KEY:
                    v ^= 0x0020
                data.append(v)
    return w, h, data

def write_still(inp, outp, name, maxw, maxh):
    img = Image.open(inp)
    allow_resize = img.size != (maxw, maxh)
    w, h, data = flatten(img, maxw, maxh, allow_resize=allow_resize)
    lines = [
        f'/* Auto-generated from {inp} ({w}x{h}). */',
        '#pragma once', '#include <stdint.h>', '',
        f'static const int {name}Width = {w};',
        f'static const int {name}Height = {h};',
        f'static const uint16_t {name}Alpha = 0x{ALPHA_KEY:04X};', '',
        f'static const uint16_t {name}Screen[{w * h}] = {{',
    ]
    for i in range(0, len(data), 12):
        row = ', '.join(f'0x{v:04X}' for v in data[i:i+12])
        lines.append(f'    {row},')
    lines.append('};')
    lines.append('')
    Path(outp).write_text('\n'.join(lines))
    print(f'wrote {outp}: {w}x{h}, {len(data)*2} bytes')

def main():
    if len(sys.argv) < 2:
        print('usage: img_to_rgb565.py input.png [-o out.h] [--name splash] [--max 240x135]')
        return
    inp = sys.argv[1]
    outp = 'splash_sprite.h'
    name = 'splash'
    maxw, maxh = 240, 135
    i = 2
    while i < len(sys.argv):
        a = sys.argv[i]
        if a in ('-o', '--out') and i + 1 < len(sys.argv):
            outp = sys.argv[i+1]; i += 2
        elif a == '--name' and i + 1 < len(sys.argv):
            name = sys.argv[i+1]; i += 2
        elif a == '--max' and i + 1 < len(sys.argv):
            mw, mh = sys.argv[i+1].split('x')
            maxw, maxh = int(mw), int(mh); i += 2
        else:
            i += 1
    os.makedirs(os.path.dirname(outp) or '.', exist_ok=True)
    write_still(inp, outp, name, maxw, maxh)

if __name__ == '__main__':
    main()
