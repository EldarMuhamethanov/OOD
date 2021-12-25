import {Shape} from "../model/Shape";
import {SelectionModel} from "../model/SelectionModel";
import {SelectionView} from "../view/SelectionView";
import {Rect} from "../common/Rect";


class SelectionController {
    private m_model: SelectionModel;
    private m_view: SelectionView;
    constructor(model: SelectionModel, view: SelectionView) {
        this.m_model = model
        this.m_view = view
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
            const left = Math.max(rect.left, 0);
            const top = Math.max(rect.top, 0);
            const right = Math.min(rect.left + rect.width, this.m_model.getCanvas().getWidth());
            const bottom = Math.min(rect.top + rect.height, this.m_model.getCanvas().getHeight());

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