include Utils;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString size =>
    switch size {
    | None => ""
    | Large => "pagination-lg"
    | Small => "pagination-sm"
    };
};

let component = ReasonReact.statelessComponent "Pagination";

let make
    tag::(tag: string)="ul"
    size::(size: Size.t)=None
    className::(className: option string)=?
    children => {
  ...component,
  render: fun _self => {
    let className = ["pagination", Size.toString size, unwrapStr i className] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": className} children
  }
};

module Item = {
  let component = ReasonReact.statelessComponent "Pagination.Item";
  let make
      tag::(tag: string)="li"
      active::(active: bool)=false
      disabled::(disabled: bool)=false
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let className =
        ["page-item", active ? "active" : "", disabled ? "disabled" : "", unwrapStr i className] |>
        String.concat " ";
      ReasonReact.createDomElement tag props::{"className": className} children
    }
  };
};

/* ToDo: onClick stuff */
module Link = {
  let component = ReasonReact.statelessComponent "Pagination.Link";
  let make
      tag::(tag: string)="a"
      ariaLabel::(ariaLabel: option string)=?
      next::(next: bool)=false
      previous::(previous: bool)=false
      href::(href: string)=""
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let ariaLabel =
        switch ariaLabel {
        | Some label => label
        | None => previous ? "Previous" : next ? "Next" : ""
        };
      /* Create the default caret arrows */
      let wrap codePoint => [|ReasonReact.stringToElement (Js.String.fromCodePoint codePoint)|];
      let prevCaret = wrap 171;
      let nextCaret = wrap 187;
      /* Use the default carets, if this is a prev or next and no children */
      let children =
        switch (Array.length children) {
        | 0 => previous ? prevCaret : next ? nextCaret : children
        | _ => children
        };
      /* A helper to wrap iff we are a prev or next element */
      let wrapChildren children => [|
        ReasonReact.createDomElement
          "span" props::{"aria-hidden": Js.Boolean.to_js_boolean true, "key": "caret"} children,
        ReasonReact.createDomElement
          "span"
          props::{"className": "sr-only", "key": "sr"}
          [|ReasonReact.stringToElement ariaLabel|]
      |];
      let wrappedChildren = previous || next ? wrapChildren children : children;
      let className = [unwrapStr i className, "page-link"] |> String.concat " ";
      ReasonReact.createDomElement
        tag props::{"className": className, "aria-label": ariaLabel, "href": href} wrappedChildren
    }
  };
};