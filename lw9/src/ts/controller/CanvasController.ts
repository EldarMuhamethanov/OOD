import { Shape } from "../model/Shape";
import {CanvasModel} from "../model/CanvasModel";
import {CanvasRenderer} from "../view/CanvasRenderer";


class CanvasController {
    private m_model: CanvasModel
    private m_renderer: CanvasRenderer

    constructor(model: CanvasModel, renderer: CanvasRenderer) {
        this.m_model = model
        this.m_renderer = renderer
    }

    addShape(shape: Shape) {
        this.m_model.addShape(shape)
    }

    removeShape(shapeId: string) {
        this.resetSelection()
        this.m_model.removeShape(shapeId)
    }

    selectShape(shape: Shape) {
        this.m_model.getSelectionModel().setSelectedShape(shape)
    }

    resetSelection() {
        this.m_model.getSelectionModel().setSelectedShape(null)
    }
}

export {
    CanvasController,
}