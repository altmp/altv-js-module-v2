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
                this.a = obj.a;
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

    static fromArray(arr) {
        return new RGBA(arr[0], arr[1], arr[2], arr[3]);
    }
    static fromObject(obj) {
        return new RGBA(obj.r, obj.g, obj.b, obj.a);
    }

    static zero = new RGBA(0, 0, 0, 0);
}
