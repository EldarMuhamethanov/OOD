import {Signal} from "../common/Signal";
import {Shape} from "./Shape";
import {SelectionModel} from "./SelectionModel";

class CanvasModel {
    private m_shapes: Array<Shape>
    private m_width: number
    private m_height: number

    private readonly m_selectionModel: SelectionModel

    private m_onShapeCreated = new Signal<Shape>()
    private m_onShapeRemoved = new Signal<string>()

    constructor(width: number, height: number, shapes: Array<Shape> = []) {
        this.m_width = width
        this.m_height = height
        this.m_shapes = shapes
        this.m_selectionModel = new SelectionModel(this)
    }

    getOnShapeCreated() {
        return this.m_onShapeCreated
    }

    getOnShapeRemoved() {
        return this.m_onShapeRemoved
    }

    getSelectionModel() {
        return this.m_selectionModel
    }

    getWidth() {
        return this.m_width
    }

    getHeight() {
        return this.m_height
    }

    getShapes() {
        return this.m_shapes
    }

    addShape(shape: Shape) {
        this.m_shapes.push(shape)
        this.m_onShapeCreated.dispatch(shape)
    }

    removeShape(shapeId: string) {
        this.m_shapes = this.m_shapes.filter(shape => shapeId !== shape.id)
        this.m_onShapeRemoved.dispatch(shapeId)
    }

    toJson() {
        const canvasWidth = this.getWidth()
        const canvasHeight = this.getHeight()
        const shapesJSON = this.getShapes().map(shape => shape.toJson())

        return {
            canvasWidth,
            canvasHeight,
            shapes: shapesJSON,
        }
    }
}

export {
    CanvasModel,
}