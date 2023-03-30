// clang-format off

export class RGBA {
    r = 0;
    g = 0;
    b = 0;
    a = 255;

    constructor(...args) {
        if(args.length >= 3) {
            this.r = args[0];
            this.g = args[1];
            this.b = args[2];
            if(args.length === 4) this.a = args[3];
        }
        else if(args.length === 1) {
            const arg = args[0];
            if(typeof arg === "object") {
                const obj = arg;
                this.r = obj.r;
                this.g = obj.g;
                this.b = obj.b;
                if(obj.a) this.a = obj.a;
            }
            else if(Array.isArray(arg)) {
                const arr = arg;
                this.r = arr[0];
                this.g = arr[1];
                this.b = arr[2];
                if(arr.length === 4) this.a = arr[3];
            }
        }
        else throw new Error("Invalid arguments");
    }

    toArray() {
        return [this.r, this.g, this.b, this.a];
    }

    toInt() {
        let int = this.r << 24;
        int |= this.g << 16;
        int |= this.b << 8;
        int |= this.a;
        return int;
    }

    static fromInt(int) {
        const r = (int >> 24) & 0xFF;
        const g = (int >> 16) & 0xFF;
        const b = (int >> 8) & 0xFF;
        const a = int & 0xFF;
        return new RGBA(r, g, b, a);
    }

    static zero = new RGBA(0, 0, 0, 0);
}
