import { Shape } from "../model/Shape";
import {CanvasModel} from "../model/CanvasModel";
import {CanvasRenderer} from "../view/CanvasRenderer";
import {SelectionModel} from "../model/SelectionModel";


class CanvasController {
    private m_model: CanvasModel
    private m_selectionModel: SelectionModel

    constructor(model: CanvasModel, selection: SelectionModel) {
        this.m_model = model
        this.m_selectionModel = selection
    }

    addShape(shape: Shape) {
        this.m_model.addShape(shape)
    }

    removeShape(shapeId: string) {
        this.resetSelection()
        this.m_model.removeShape(shapeId)
    }

    selectShape(shape: Shape) {
        this.m_selectionModel.setSelectedShape(shape)
    }

    resetSelection() {
        this.m_selectionModel.setSelectedShape(null)
    }
}

export {
    CanvasController,
}