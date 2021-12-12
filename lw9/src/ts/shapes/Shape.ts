import {ISignal, Signal} from "../Signal";
import {ShapeType} from "../ShapeType";
import {generateUid} from "../common/generateUid";

class Shape
{
    private m_width: number
    private m_height: number
    private m_left: number
    private m_top: number
    private m_isSelected: boolean
    private readonly m_shapeType: ShapeType
    private readonly m_id: string
    private onRectChange: ISignal<void> = new Signal<void>()
    private onSelectedChange: ISignal<void> = new Signal<void>()

    constructor (width: number, height: number, top: number, left: number, shapeType: ShapeType) {
        this.m_width = width
        this.m_height = height
        this.m_left = left
        this.m_top = top
        this.m_shapeType = shapeType
        this.m_id = generateUid()
        this.m_isSelected = false
    }

    getOnRectChange() {
        return this.onRectChange
    }

    getOnSelectedChange() {
        return this.onSelectedChange
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
    setRect(left: number, top: number, width: number, height: number) {
        this.m_top = top
        this.m_left = left
        this.m_width = width
        this.m_height = height
        this.onRectChange.dispatch()
    }
    setSelected(selected: boolean) {
        this.m_isSelected = selected
        this.onSelectedChange.dispatch()
    }
    get isSelected() {
        return this.m_isSelected
    }
    get left() {
        return this.m_left
    }
    get top() {
        return this.m_top
    }
}

export {
    Shape,
}