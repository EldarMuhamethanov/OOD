import {ShapeRenderer} from "./ShapeRenderer";
import {Shape} from "../model/Shape";
import {CanvasRenderer} from "./CanvasRenderer";


class EllipseRenderer extends ShapeRenderer
{
    constructor(model: Shape) {
        super(model)
    }
    protected getShapeHtmlImpl(): SVGGraphicsElement {
        const model = this.model
        const width = model.width
        const height = model.height
        const ellipse = document.createElementNS('http://www.w3.org/2000/svg', 'ellipse')
        ellipse.setAttribute('rx', `${width / 2}`)
        ellipse.setAttribute('ry', `${height / 2}`)
        ellipse.setAttribute('cx', `${width / 2}`)
        ellipse.setAttribute('cy', `${height / 2}`)
        ellipse.setAttribute('fill', 'green')
        return ellipse
    }
}

export {
    EllipseRenderer,
}