'use strict'

class ObjectManager {
    constructor() {
        this.objects = [];
    }

    update() {
        this.objects.forEach(function (object) {
            object.update();
        });
    }
    draw(ctx) {
        this.objects.forEach(function (object) {
            object.draw(ctx);
        });

    }
    addObject(object) {
        this.objects.push(object);
    }

    deleteAll() {
        this.objects = [];
    }

    deleteObject(i) {
        this.objects.splice(i, 1);
    }


}

console.log("Loaded ObjectManager.js")
