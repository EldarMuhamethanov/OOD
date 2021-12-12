"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.TriangleRenderer = void 0;
var ShapeRenderer_1 = require("./ShapeRenderer");
var TriangleRenderer = /** @class */ (function (_super) {
    __extends(TriangleRenderer, _super);
    function TriangleRenderer(model, canvas) {
        return _super.call(this, model, canvas) || this;
    }
    TriangleRenderer.prototype.getShapeHtmlImpl = function () {
        var model = this.model;
        var width = model.width;
        var height = model.height;
        return "<svg\n            xmlns='http://www.w3.org/2000/svg'\n            width='100%'\n            height='100%'\n            viewPort='0 0 ".concat(width, " ").concat(height, "'>\"\n            <polygon points='").concat(0, ",").concat(height, " ").concat(width, ",").concat(height, " ").concat(width / 2, ",").concat(0, "' fill='yellow' />\n        </svg>");
    };
    return TriangleRenderer;
}(ShapeRenderer_1.ShapeRenderer));
exports.TriangleRenderer = TriangleRenderer;
//# sourceMappingURL=Triangle.js.map