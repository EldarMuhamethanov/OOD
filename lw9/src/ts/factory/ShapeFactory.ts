import {ShapeType} from "../common/ShapeType";
import {Shape} from "../model/Shape";
import {RectangleRenderer} from "../view/Rectangle";
import {EllipseRenderer} from "../view/Ellipse";
import {TriangleRenderer} from "../view/Triangle";
import {CanvasModel} from "../model/CanvasModel";
import {CanvasRenderer} from "../view/CanvasRenderer";

const DEFAULT_WIDTH = 100
const DEFAULT_HEIGHT = 70

type ShapeModelType = {
    shapeType: ShapeType,
    canvas: CanvasModel,
    width?: number,
    height?: number,
    left?: number,
    top?: number,
}

class ShapeFactory {
    static createShapeModel({
        shapeType,
        canvas,
        width = DEFAULT_WIDTH,
        height = DEFAULT_HEIGHT,
        left = canvas.getWidth() / 2 - DEFAULT_HEIGHT / 2,
        top = canvas.getHeight() / 2 - DEFAULT_HEIGHT / 2,
    }: ShapeModelType) {
        return new Shape(
            width,
            height,
            top,
            left,
            shapeType,
        )
    }

    static createShapeRenderer(model: Shape, canvas: CanvasModel) {
        switch (model.shapeType) {
            case "rectangle":
                return new RectangleRenderer(model, canvas)
            case "ellipse":
                return new EllipseRenderer(model, canvas)
            case "triangle":
                return new TriangleRenderer(model, canvas)
        }
    }
}

export {
    ShapeFactory,
}