import {Shape} from "../model/Shape";
import {ShapeRenderer} from "./ShapeRenderer";
import {CanvasModel} from "../model/CanvasModel";

class RectangleRenderer extends ShapeRenderer
{
    private m_implElement: SVGGraphicsElement = document.createElementNS('http://www.w3.org/2000/svg', 'polygon')
    constructor(model: Shape, canvas: CanvasModel) {
        super(model, canvas)
    }
    protected updateSvgBounds() {
        const model = this.model
        const width = model.width
        const height = model.height
        this.m_implElement.setAttribute('points', `${0},${0} ${width},${0} ${width},${height} ${0},${height}`)
        this.m_implElement.setAttribute('fill', 'black')
    }

    protected getShapeHtmlImpl(): SVGGraphicsElement {
        return this.m_implElement
    }
}

export {
    RectangleRenderer,
}