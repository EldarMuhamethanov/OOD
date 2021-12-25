import {ISignal, Signal} from "../common/Signal";
import {ShapeType} from "../common/ShapeType";
import {generateUid} from "../common/generateUid";
import {CanvasModel} from "./CanvasModel";

class Shape
{
    private m_width: number
    private m_height: number
    private m_left: number
    private m_top: number
    private readonly m_shapeType: ShapeType
    private readonly m_id: string
    private readonly m_canvas: CanvasModel
    private onRectChange: ISignal<void> = new Signal<void>()

    constructor (canvas: CanvasModel, width: number, height: number, top: number, left: number, shapeType: ShapeType) {
        this.m_canvas = canvas
        this.m_width = width
        this.m_height = height
        this.m_left = left
        this.m_top = top
        this.m_shapeType = shapeType
        this.m_id = generateUid()
    }

    getOnRectChange() {
        return this.onRectChange
    }

    get id() {
        return this.m_id
    }

    get shapeType() {
        return this.m_shapeType
    }

    get width() {
        return this.m_width
    }
    get height() {
        return this.m_height
    }
    get canvas() {
        return this.m_canvas
    }
    setRect(left: number, top: number, width: number, height: number) {
        this.m_top = top
        this.m_left = left
        this.m_width = width
        this.m_height = height
        this.onRectChange.dispatch()
    }
    get left() {
        return this.m_left
    }
    get top() {
        return this.m_top
    }

    toJson() {
        return {
            id: this.id,
            left: this.left,
            top: this.top,
            type: this.shapeType,
            width: this.width,
            height: this.height,
        }
    }
}

export {
    Shape,
}