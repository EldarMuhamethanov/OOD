import {ShapeRenderer} from "./ShapeRenderer";
import {Shape} from "./Shape";
import {Canvas} from "../Canvas/Canvas";


class EllipseRenderer extends ShapeRenderer
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
            <ellipse rx='${width / 2}' ry='${height / 2}' cx='${width / 2}' cy='${height / 2}' fill="green" />
        </svg>`
    }
}

export {
    EllipseRenderer,
}