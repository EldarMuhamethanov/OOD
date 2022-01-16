import {Shape} from "../model/Shape";
import {ShapeRenderer} from "./ShapeRenderer";
import {CanvasRenderer} from "./CanvasRenderer";
import {CanvasModel} from "../model/CanvasModel";

class TriangleRenderer extends ShapeRenderer
{
    private m_implElement: SVGGraphicsElement = document.createElementNS('http://www.w3.org/2000/svg', 'polygon')
    constructor(model: Shape, canvas: CanvasModel) {
        super(model, canvas)
    }
    protected updateSvgBounds() {
        const model = this.model
        const width = model.width
        const height = model.height
        this.m_implElement.setAttribute('points', `${0},${height} ${width},${height} ${width / 2},${0}`)
        this.m_implElement.setAttribute('fill', 'yellow')
    }
    protected getShapeHtmlImpl(): SVGGraphicsElement {
        return this.m_implElement
    }
}

export {
    TriangleRenderer,
}