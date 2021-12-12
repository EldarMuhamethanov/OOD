import { Shape } from "./Shape";
import { ShapeRenderer} from "./ShapeRenderer";
import {Canvas} from "../Canvas/Canvas";

class RectangleRenderer extends ShapeRenderer
{
    constructor(model: Shape, canvas: Canvas) {
        super(model, canvas)
    }
    protected getShapeHtmlImpl(): string {
        const model = this.model
        const width = model.width
        const height = model.height
        return `<svg
            xmlns='http://www.w3.org/2000/svg'
            width='${width}'
            height='${height}'
            viewPort='0 0 ${width} ${height}'>"
            <polygon points='${0},${0} ${width},${0} ${width},${height} ${0},${height}' fill='black' />
        </svg>`
    }
}

export {
    RectangleRenderer,
}