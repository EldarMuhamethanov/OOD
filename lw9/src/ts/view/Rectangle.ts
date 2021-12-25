import {Shape} from "../model/Shape";
import {ShapeRenderer} from "./ShapeRenderer";

class RectangleRenderer extends ShapeRenderer
{
    constructor(model: Shape) {
        super(model)
    }
    protected getShapeHtmlImpl(): SVGGraphicsElement {
        const model = this.model
        const width = model.width
        const height = model.height
        const polygon = document.createElementNS('http://www.w3.org/2000/svg', 'polygon')
        polygon.setAttribute('points', `${0},${0} ${width},${0} ${width},${height} ${0},${height}`)
        polygon.setAttribute('fill', 'black')
        return polygon
    }
}

export {
    RectangleRenderer,
}