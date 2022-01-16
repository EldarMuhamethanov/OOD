import {Shape} from "./Shape";
import {Signal} from "../common/Signal";


class SelectionModel {
    private m_selectedShape: Shape | null = null
    private m_onSelectedShapeChanged = new Signal<void>()

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