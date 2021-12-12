import {Signal} from "../Signal";
import {Shape} from "../shapes/Shape";


class EditorModel {
    private m_shapes: Array<Shape> = []
    private m_selectedShape: string | null = null
    private m_onSelectedShapeChanged = new Signal<void>()
    private m_onShapeCreated = new Signal<Shape>()
    private m_onShapeRemoved = new Signal<string>()

    getOnShapeCreated() {
        return this.m_onShapeCreated
    }

    getOnShapeRemoved() {
        return this.m_onShapeRemoved
    }

    getOnSelectedShapeChanged() {
        return this.m_onSelectedShapeChanged
    }

    getSelectedShape() {
        return this.m_selectedShape
    }

    getShapes() {
        return this.m_shapes
    }

    setSelectedShape(shapeId: string|null) {
        if (shapeId !== this.m_selectedShape) {
            this.m_selectedShape = shapeId
            if (shapeId) {
                const shape = this.m_shapes.find(shape => shape.id === shapeId)
                if (shape) {
                    this.m_shapes = this.m_shapes.filter(shape => shape.id !== shapeId)
                    this.m_shapes.push(shape)
                }
            }
            this.m_onSelectedShapeChanged.dispatch()
        }
    }

    addShape(shape: Shape) {
        this.m_shapes.push(shape)
        this.m_onShapeCreated.dispatch(shape)
    }

    removeSelectedShape() {
        if (this.m_selectedShape) {
            this.m_shapes = this.m_shapes.filter(shape => this.m_selectedShape !== shape.id)
            const currentSelectedShape = this.m_selectedShape
            this.m_selectedShape = null
            this.m_onShapeRemoved.dispatch(currentSelectedShape)
        }
    }
}

export {
    EditorModel,
}