import { Position } from "../common/Position";
import {Shape} from "../model/Shape";
import {ShapeRenderer} from "../view/ShapeRenderer";
import {Rect} from "../common/Rect";
import {CanvasModel} from "../model/CanvasModel";

class ShapeController
{
    private m_model: Shape;
    private m_canvasModel: CanvasModel
    constructor(model: Shape, canvasModel: CanvasModel) {
        this.m_model = model
        this.m_canvasModel = canvasModel
    }

    shapeMove(position: Position) {
        const left = position.left
        const top = position.top
        const width = this.m_model.width
        const height = this.m_model.height

        this.m_model.setRect(
            Math.min(Math.max(left, 0), this.m_canvasModel.getWidth() - width),
            Math.min(Math.max(top, 0), this.m_canvasModel.getHeight() - height),
            width,
            height
        )
    }
}

export {
    ShapeController,
}