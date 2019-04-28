include Utils;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString = size =>
    switch (size) {
    | None => ""
    | Large => "pagination-lg"
    | Small => "pagination-sm"
    };
};

let component = ReasonReact.statelessComponent("Pagination");

[@react.component]
let make = (~size: Size.t=None, ~className: option(string)=?, ~children) => {
  let className = ["pagination", Size.toString(size), unwrapStr(i, className)] |> String.concat(" ");
  <ul className> children </ul>;
};

module Item = {
  [@react.component]
  let make = (~active: bool=false, ~disabled: bool=false, ~className: option(string)=?, ~children) => {
    let className =
      ["page-item", active ? "active" : "", disabled ? "disabled" : "", unwrapStr(i, className)]
      |> String.concat(" ");
      <li className> children </li>
  };
};

module Link = {
  [@react.component]
  let make =
      (
        ~ariaLabel: option(string)=?,
        ~next: bool=false,
        ~previous: bool=false,
        ~href: string="",
        ~onClick: option(ReactEvent.Mouse.t => unit)=?,
        ~className: option(string)=?,
        ~children:option(React.element)=?,
      ) => {        
    let ariaLabel =
      switch (ariaLabel) {
      | Some(label) => label
      | None => previous ? "Previous" : next ? "Next" : ""
      };
    let wrap = codePoint => React.string(Js.String.fromCodePoint(codePoint));
    let prevCaret = wrap(171);
    let nextCaret = wrap(187);
 
    let children = switch((previous,next,children))  {
      | (true, _, _ ) => prevCaret
      | (false, true, _) => nextCaret
      | (false, false, Some(child)) => child
      | (false, false, None) => React.string("ERROR")
    };
 
    let wrapChildren = children:React.element =>
      React.array(
       [| <span ariaHidden=true key="caret"> children </span>,
        <span className="sr-only" key="sr"> {React.string(ariaLabel)} </span> |]
      );

    let wrappedChildren = previous || next ? wrapChildren(children) : children;
    let className = [unwrapStr(i, className), "page-link"] |> String.concat(" ");
    <a className ariaLabel href ?onClick> wrappedChildren </a>
  }
};

/* ToDo: onClick stuff */
