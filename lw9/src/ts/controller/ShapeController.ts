import { Position } from "../common/Position";
import {Shape} from "../model/Shape";
import {ShapeRenderer} from "../view/ShapeRenderer";
import {Rect} from "../common/Rect";

class ShapeController
{
    private m_model: Shape;
    private m_view: ShapeRenderer;
    constructor(model: Shape, view: ShapeRenderer) {
        this.m_model = model
        this.m_view = view
    }

    shapeMove(position: Position) {
        const left = position.left
        const top = position.top
        const width = this.m_model.width
        const height = this.m_model.height

        this.m_model.setRect(
            Math.min(Math.max(left, 0), this.m_model.canvas.getWidth() - width),
            Math.min(Math.max(top, 0), this.m_model.canvas.getHeight() - height),
            width,
            height
        )
    }
}

export {
    ShapeController,
}