import { Shape } from "./Shape";
import {ShapeRenderer} from "./ShapeRenderer";
import {Canvas} from "../Canvas/Canvas";

class TriangleRenderer extends ShapeRenderer
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
            width='100%'
            height='100%'
            viewPort='0 0 ${width} ${height}'>"
            <polygon points='${0},${height} ${width},${height} ${width / 2},${0}' fill='yellow' />
        </svg>`
    }
}

export {
    TriangleRenderer,
}