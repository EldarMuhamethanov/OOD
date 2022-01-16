import {CanvasModel} from "../model/CanvasModel";
import {Shape} from "../model/Shape";

abstract class ISerializer {
    abstract serializeCanvas(canvas: CanvasModel): string;
}

class JSONSerializer implements ISerializer {
    serializeCanvas(canvas: CanvasModel): string {
        return JSON.stringify({
            canvasWidth: canvas.getWidth(),
            canvasHeight: canvas.getHeight(),
            shapes: canvas.getShapes().map(shape => this.serializeShape(shape)),
        })
    }
    private serializeShape(shape: Shape): string {
        return JSON.stringify({
            id: shape.id,
            left: shape.left,
            top: shape.top,
            type: shape.shapeType,
            width: shape.width,
            height: shape.height,
        })
    }
}

export {
    ISerializer,
    JSONSerializer,
}