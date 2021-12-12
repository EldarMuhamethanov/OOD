import {Shape} from "./Shape";
import {ShapeRenderer} from "./ShapeRenderer";

class ShapeController
{
    private m_model: Shape;
    private m_view: ShapeRenderer;
    constructor(model: Shape, view: ShapeRenderer) {
        this.m_model = model
        this.m_view = view
    }

    setRect(left: number, top: number, width: number, height: number) {
        this.m_model.setRect(left, top, width, height)
    }

    setPosition(left: number, top: number) {
        this.m_model.setRect(left, top, this.m_model.width, this.m_model.height)
    }

    setSize(width: number, height: number) {
        this.m_model.setRect(this.m_model.left, this.m_model.top, width, height)
    }

    setIsSelected(isSelected: boolean) {
        this.m_model.setSelected(isSelected)
    }
}

export {
    ShapeController,
}