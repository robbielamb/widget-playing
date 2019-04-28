include Utils;

/* Layout items */
module Container = {
  [@react.component]
  let make =
      (
        ~fluid: bool=false,
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        ~children,
      ) => {
    let className =
      [fluid ? "container-fluid" : "container", unwrapStr(i, className)]
      |> String.concat(" ");
    <div className> children </div>;
  };
};

module Row = {
  /* Todo: Add more options here */
  [@react.component]
  let make =
      (
        ~noGutters: bool=false,
        ~className: option(string)=? /* cssModule::(cssModule: option (Js.t {..}))=? */,
        ~children,
      ) => {
    let classes =
      ["row", noGutters ? "no-gutters" : "", unwrapStr(i, className)]
      |> String.concat(" ");
    //ReactDOMRe.createElementVariadic(tag, ~props={"className": classes}->ReactDOMRe.objToDOMProps, children);
    <div className=classes> children </div>;
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
  let shape =
      (
        ~size: option(size)=?,
        ~push: option(int)=?,
        ~pull: option(int)=?,
        ~offset: option(int)=?,
        (),
      ) => {
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

  let mySHape = shape(());

  [@react.component]
  let make =
      (
        ~xs: option(shape)=?,
        ~sm: option(shape)=?,
        ~md: option(shape)=?,
        ~lg: option(shape)=?,
        ~xl: option(shape)=?,
        ~className: option(string)=?,
        ~children,
      ) => {
    let classShapeList = processShapeList(xs, sm, md, lg, xl);
    let classes =
      Belt.List.concat([unwrapStr(i, className)], classShapeList)
      |> String.concat(" ");
    //ReactDOMRe.createElementVariadic(tag, ~props={"className": classes}->ReactDOMRe.objToDOMProps, children)
    <div className=classes> children </div>;
  };
};