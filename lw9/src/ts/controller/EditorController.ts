import {EditorModel} from "../model/EditorModel";
import {EditorRenderer} from "../view/EditorRenderer";
import {ShapeType} from "../common/ShapeType";
import { ShapeFactory } from "../factory/ShapeFactory";

class EditorController {
    private m_model: EditorModel
    private m_renderer: EditorRenderer

    constructor(model: EditorModel, renderer: EditorRenderer) {
        this.m_model = model
        this.m_renderer = renderer
    }

    addShape(shapeType: ShapeType) {
        const canvasModel = this.m_model.canvasModel
        canvasModel.addShape(ShapeFactory.createShapeModel({
            shapeType,
            canvas: canvasModel,
        }))
    }

    deleteSelectedShape() {
        const selectedShape = this.m_model.canvasModel.getSelectionModel().getSelectedShape()
        if (selectedShape) {
            this.m_model.canvasModel.removeShape(selectedShape.id)
            this.m_model.canvasModel.getSelectionModel().setSelectedShape(null)
        }
    }

    uploadFile() {
        this.m_model.uploadFile()
    }

    saveEditor() {
        this.m_model.saveEditor()
    }
}

export {
    EditorController,
}