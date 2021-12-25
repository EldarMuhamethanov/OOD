import {Shape} from "../model/Shape";
import {ShapeRenderer} from "./ShapeRenderer";
import {CanvasRenderer} from "./CanvasRenderer";

class TriangleRenderer extends ShapeRenderer
{
    constructor(model: Shape) {
        super(model)
    }
    protected getShapeHtmlImpl(): SVGGraphicsElement {
        const model = this.model
        const width = model.width
        const height = model.height
        const polygon = document.createElementNS('http://www.w3.org/2000/svg', 'polygon')
        polygon.setAttribute('points', `${0},${height} ${width},${height} ${width / 2},${0}`)
        polygon.setAttribute('fill', 'yellow')
        return polygon
    }
}

export {
    TriangleRenderer,
}