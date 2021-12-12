import { Position } from "../shapes/Position";
import {ISignal, Signal} from "../Signal";

class DragNDropHandler {
    private m_element: HTMLElement
    private onMoveSignal: ISignal<Position> = new Signal<Position>()
    private onDragStart: ISignal<void> = new Signal()
    constructor(element: HTMLElement) {
        this.m_element = element

        this.m_element.onmousedown = e => {
            if (!e.defaultPrevented) {
                e.preventDefault()
                this.onDragStart.dispatch()
                this.onShapeMouseDown(e)
            }
        }
    }

    getOnDragStart() {
        return this.onDragStart
    }

    getOnMoveSignal() {
        return this.onMoveSignal
    }

    private onShapeMouseUp() {
        window.onmousemove = null
        window.onmouseup = null
    }

    private onShapeMove(e: MouseEvent, leftOffset: number, topOffset: number) {
        this.onMoveSignal.dispatch({
            left: e.x - leftOffset,
            top: e.y - topOffset,
        })
    }

    private onShapeMouseDown(e: MouseEvent) {
        const elementBounds = this.m_element.getBoundingClientRect()
        const resultLeftOffset = (e.x - elementBounds.left)
        const resultTopOffset = (e.y - elementBounds.top)

        window.onmousemove = e => this.onShapeMove(e, resultLeftOffset, resultTopOffset)
        window.onmouseup = () => this.onShapeMouseUp()
    }
}

export {
    DragNDropHandler,
}

export type {
    Position,
}