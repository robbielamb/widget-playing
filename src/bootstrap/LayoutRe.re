include Utils;

/* Layout items */
module Container = {
  let component = ReasonReact.statelessComponent("Container");
  let make =
      (
        ~fluid: bool=false,
        ~tag: string="div",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */ children,
      ) => {
    ...component,
    render: _self => {
      let classes = [fluid ? "container-fluid" : "container", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(tag, ~props={"className": classes}->ReactDOMRe.objToDOMProps, children);
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "fluid": option('fluid),
          "children": 'children,
        },
      ) =>
      make(~className=?reactProps##className, ~tag=?reactProps##tag, ~fluid=?reactProps##fluid, reactProps##children)
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~fluid: 'fluid=?, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "fluid": option('fluid),
      "children": 'children,
    } =
    "";
};

module Row = {
  /* Todo: Add more options here */
  //let component = ReasonReact.statelessComponent("Row");
  [@react.component]
  let make =
      (
        ~noGutters: bool=false,
        ~tag: string="div",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */ ~children,
      ) => {
    let classes = ["row", noGutters ? "no-gutters" : "", unwrapStr(i, className)] |> String.concat(" ");
    //ReactDOMRe.createElementVariadic(tag, ~props={"className": classes}->ReactDOMRe.objToDOMProps, children);
    <div className=classes> children </div>
  };
};

module ColSizes = {
  type size =
    | Auto
    | Size(int);
  type shape = {
    size: option(size),
    push: option(int),
    pull: option(int),
    offset: option(int),
  };
  let shape = (~size: option(size)=?, ~push: option(int)=?, ~pull: option(int)=?, ~offset: option(int)=?, ()) => {
    size,
    push,
    pull,
    offset,
  };
  let genClasses = (colWidth: string, shape: shape) => {
    let isXs = "xs" == colWidth;
    let interfix = isXs ? "-" : {j|-$(colWidth)-|j};
    let colClass =
      switch (shape.size) {
      | Some(Auto) => {j|col$(interfix)auto|j}
      | Some(Size(size)) => {j|col$(interfix)$(size)|j}
      | None => isXs ? "col" : {j|col-$(colWidth)|j}
      };
    let formatClass = (name, intensity) => {
      let colSize = string_of_int(intensity);
      {j|$(name)$(interfix)$(colSize)|j};
    };
    let colPush =
      switch (shape.push) {
      | Some(push) => formatClass("push", push)
      | None => ""
      };
    let colPull =
      switch (shape.pull) {
      | Some(pull) => formatClass("pull", pull)
      | None => ""
      };
    let colOffset =
      switch (shape.offset) {
      | Some(offset) => formatClass("offset", offset)
      | None => ""
      };
    [colClass, colPush, colPull, colOffset];
  };
  let processShapeList = (xs, sm, md, lg, xl) =>
    [("xs", xs), ("sm", sm), ("md", md), ("lg", lg), ("xl", xl)]
    ->(
        Belt.List.map(((col, maybeShape)) =>
          switch (maybeShape) {
          | None => []
          | Some(shape) => genClasses(col, shape)
          }
        )
      )
    ->Belt.List.flatten;
};

module Col = {
  include ColSizes;
  [@react.component]
  let make =
      (
        ~tag: string="div",
        ~xs: option(shape)=?,
        ~sm: option(shape)=?,
        ~md: option(shape)=?,
        ~lg: option(shape)=?,
        ~xl: option(shape)=?,
        ~className: option(string)=?,
        ~children,
      ) => {
    let classShapeList = processShapeList(xs, sm, md, lg, xl);
    let classes = Belt.List.concat([unwrapStr(i, className)], classShapeList) |> String.concat(" ");
    //ReactDOMRe.createElementVariadic(tag, ~props={"className": classes}->ReactDOMRe.objToDOMProps, children)
    <div className=classes> children </div>

  };
};