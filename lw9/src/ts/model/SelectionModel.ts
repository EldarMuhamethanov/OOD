import {Shape} from "./Shape";
import {Signal} from "../common/Signal";
import {CanvasModel} from "./CanvasModel";


class SelectionModel {
    private m_canvas: CanvasModel
    private m_selectedShape: Shape | null = null
    private m_onSelectedShapeChanged = new Signal<void>()

    constructor(canvas: CanvasModel) {
        this.m_canvas = canvas
    }

    getCanvas() {
        return this.m_canvas
    }

    onSelectedShapeChanged() {
        return this.m_onSelectedShapeChanged
    }

    setSelectedShape(shape: Shape | null) {
        this.m_selectedShape = shape
        this.m_onSelectedShapeChanged.dispatch()
    }

    getSelectedShape() {
        return this.m_selectedShape
    }
}

export {
    SelectionModel
}