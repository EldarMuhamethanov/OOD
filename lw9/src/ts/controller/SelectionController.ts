import {Shape} from "../model/Shape";
import {SelectionModel} from "../model/SelectionModel";
import {SelectionView} from "../view/SelectionView";
import {Rect} from "../common/Rect";
import {CanvasModel} from "../model/CanvasModel";


class SelectionController {
    private m_model: SelectionModel;
    private m_canvasModel: CanvasModel
    constructor(model: SelectionModel, canvasModel: CanvasModel) {
        this.m_model = model
        this.m_canvasModel = canvasModel
    }

    selectShape(shape: Shape) {
        this.m_model.setSelectedShape(shape)
    }

    resetSelection() {
        this.m_model.setSelectedShape(null)
    }

    resize(rect: Rect) {
        const selectedShape = this.m_model.getSelectedShape()
        if (selectedShape) {
            const canvas = this.m_canvasModel
            const left = Math.max(rect.left, 0)
            const top = Math.max(rect.top, 0)
            const right = Math.min(rect.left + rect.width, canvas.getWidth())
            const bottom = Math.min(rect.top + rect.height, canvas.getHeight())

            selectedShape.setRect(
                left,
                top,
                right - left,
                bottom - top,
            )
        }
    }
}

export {
    SelectionController
}