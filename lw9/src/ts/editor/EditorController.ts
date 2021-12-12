import { Shape } from "../shapes/Shape";
import {EditorModel} from "./EditorModel";
import {EditorRenderer} from "./EditorRenderer";


class EditorController {
    private m_model: EditorModel
    private m_renderer: EditorRenderer

    constructor(model: EditorModel, renderer: EditorRenderer) {
        this.m_model = model
        this.m_renderer = renderer
    }

    addShape(shape: Shape) {
        this.m_model.addShape(shape)
    }

    removeSelectedShape() {
        this.m_model.removeSelectedShape()
    }

    setSelectedShape(shapeId: string | null) {
        this.m_model.setSelectedShape(shapeId)
    }
}

export {
    EditorController,
}