import {EditorModel} from "../model/EditorModel";
import {ShapeType} from "../common/ShapeType";
import {ShapeFactory} from "../factory/ShapeFactory";
import {SelectionModel} from "../model/SelectionModel";

class EditorController {
    private m_model: EditorModel
    private m_selectionModel: SelectionModel

    constructor(model: EditorModel, selectionModel: SelectionModel) {
        this.m_model = model
        this.m_selectionModel = selectionModel
    }

    addShape(shapeType: ShapeType) {
        const canvasModel = this.m_model.canvasModel
        canvasModel.addShape(ShapeFactory.createShapeModel({
            shapeType,
            canvas: canvasModel,
        }))
    }

    deleteSelectedShape() {
        const canvasModel = this.m_model.canvasModel
        const selectedShape = this.m_selectionModel.getSelectedShape()
        if (selectedShape) {
            canvasModel.removeShape(selectedShape.id)
            this.m_selectionModel.setSelectedShape(null)
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