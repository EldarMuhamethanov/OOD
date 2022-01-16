import { Position } from "../common/Position";
import {ISignal, Signal} from "../common/Signal";

class DragNDropHandler {
    private m_element: SVGGraphicsElement
    private onMoveSignal: ISignal<Position> = new Signal<Position>()

    private onShapeMouseDownCallback: (e: MouseEvent) => void = () => {}
    private onShapeMouseMoveCallback: (e: MouseEvent) => void = () => {}
    private onShapeMouseUpCallback: () => void = () => {}

    constructor(element: SVGGraphicsElement) {
        this.m_element = element
        this.onShapeMouseDownCallback = (e: MouseEvent) => this.onShapeMouseDown(e)
        this.m_element.addEventListener('mousedown', this.onShapeMouseDownCallback)
    }

    getOnMoveSignal() {
        return this.onMoveSignal
    }

    private onShapeMouseUp() {
        window.removeEventListener('mousemove', this.onShapeMouseMoveCallback)
        window.removeEventListener('mouseup', this.onShapeMouseUpCallback)
    }

    private onShapeMove(e: MouseEvent, leftOffset: number, topOffset: number) {
        this.onMoveSignal.dispatch({
            left: e.x - leftOffset,
            top: e.y - topOffset,
        })
    }

    private onShapeMouseDown(e: MouseEvent) {
        if (!e.defaultPrevented) {
            e.preventDefault()
            const elementBounds = this.m_element.getBoundingClientRect()
            const resultLeftOffset = (e.x - elementBounds.left)
            const resultTopOffset = (e.y - elementBounds.top)

            this.onShapeMouseMoveCallback = (e: MouseEvent) => this.onShapeMove(e, resultLeftOffset, resultTopOffset)
            this.onShapeMouseUpCallback = () => this.onShapeMouseUp()
            window.addEventListener('mousemove', this.onShapeMouseMoveCallback)
            window.addEventListener('mouseup', this.onShapeMouseUpCallback)
        }
    }
}

export {
    DragNDropHandler,
}

export type {
    Position,
}