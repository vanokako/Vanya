'use strict'

class EventsManager {
    constructor() {
        this.events = [];
        document.body.addEventListener("keydown", this.onKeyDown);
        document.body.addEventListener("keyup", this.onKeyUp);
    }
    //При нажатии кнопки
    onKeyDown(event) {
        eventsManager.events.push(event.key)
    }

    popEvent() {
        let event = this.events.pop();
        if (event)
            return event;
        return null;
    }
};

console.log("Loaded EventsManager.js")
