include Utils;

/* Layout items */
module Container = {
  let component = ReasonReact.statelessComponent "Container";
  let make
      fluid::(fluid: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes =
        [fluid ? "container-fluid" : "container", unwrapStr i className] |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Row = {
  /* Todo: Add more options here */
  let component = ReasonReact.statelessComponent "Row";
  let make
      noGutters::(noGutters: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes =
        ["row", noGutters ? "no-gutters" : "", unwrapStr i className] |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Col = {
  let component = ReasonReact.statelessComponent "Col";
  type size =
    | Auto
    | Size int;
  type shape = {
    size: option size,
    push: option int,
    pull: option int,
    offset: option int
  };
  let shape
      size::(size: option size)=?
      push::(push: option int)=?
      pull::(pull: option int)=?
      offset::(offset: option int)=?
      () => {
    size,
    push,
    pull,
    offset
  };
  let genClasses (colWidth: string) (shape: shape) => {
    let isXs = "xs" == colWidth;
    let interfix = isXs ? "-" : {j|-$(colWidth)-|j};
    let colClass =
      cn (
        switch shape.size {
        | Some Auto => {j|col$(interfix)auto|j}
        | Some (Size size) => {j|col$(interfix)$(size)|j}
        | None => isXs ? "col" : {j|col-$(colWidth)|j}
        }
      );
    let formatClass name intensity => {
      let colSize = string_of_int intensity;
      {j|$(name)$(interfix)$(colSize)|j}
    };
    let colPush =
      ocn (
        switch shape.push {
        | Some push => (formatClass "push" push, true)
        | None => ("", false)
        }
      );
    let colPull =
      ocn (
        switch shape.pull {
        | Some pull => (formatClass "pull" pull, true)
        | None => ("", false)
        }
      );
    let colOffset =
      ocn (
        switch shape.offset {
        | Some offset => (formatClass "offset" offset, true)
        | None => ("", false)
        }
      );
    [colClass, colPush, colPull, colOffset]
  };
  let make
      tag::(tag: string)="div"
      xs::(xs: option shape)=(Some (shape ()))
      sm::(sm: option shape)=?
      md::(md: option shape)=?
      lg::(lg: option shape)=?
      xl::(xl: option shape)=?
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classShapeList =
        [("xs", xs), ("sm", sm), ("md", md), ("lg", lg), ("xl", xl)] |>
        List.map (
          fun (col, maybeShape) =>
            switch maybeShape {
            | None => []
            | Some shape => genClasses col shape
            }
        ) |> List.flatten;
      let classes = classNameReduce className classShapeList;
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Jumbotron = {
  let component = ReasonReact.statelessComponent "Jumbotron";
  let make
      fluid::(fluid: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self => {
      let classes =
        ["jumbotron", fluid ? "jumbotron-fluid" : "", unwrapStr i className] |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};