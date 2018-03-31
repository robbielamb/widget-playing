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

let make =
    (
      ~tag: string="ul",
      ~size: Size.t=None,
      ~className: option(string)=?,
      children
    ) => {
  ...component,
  render: _self => {
    let className =
      ["pagination", Size.toString(size), unwrapStr(i, className)]
      |> String.concat(" ");
    ReasonReact.createDomElement(
      tag,
      ~props={"className": className},
      children
    );
  }
};

module Item = {
  let component = ReasonReact.statelessComponent("Pagination.Item");
  let make =
      (
        ~tag: string="li",
        ~active: bool=false,
        ~disabled: bool=false,
        ~className: option(string)=?,
        children
      ) => {
    ...component,
    render: _self => {
      let className =
        [
          "page-item",
          active ? "active" : "",
          disabled ? "disabled" : "",
          unwrapStr(i, className)
        ]
        |> String.concat(" ");
      ReasonReact.createDomElement(
        tag,
        ~props={"className": className},
        children
      );
    }
  };
};

/* ToDo: onClick stuff */
module Link = {
  let component = ReasonReact.statelessComponent("Pagination.Link");
  let make =
      (
        ~tag: string="a",
        ~ariaLabel: option(string)=?,
        ~next: bool=false,
        ~previous: bool=false,
        ~href: string="",
        ~onClick: option(ReactEventRe.Mouse.t => unit)=?,
        ~className: option(string)=?,
        children
      ) => {
    ...component,
    render: _self => {
      let ariaLabel =
        switch (ariaLabel) {
        | Some(label) => label
        | None => previous ? "Previous" : next ? "Next" : ""
        };
      let wrap = codePoint => [|
        ReasonReact.stringToElement(Js.String.fromCodePoint(codePoint))
      |];
      let prevCaret = wrap(171);
      let nextCaret = wrap(187);
      let children =
        switch (Array.length(children)) {
        | 0 => previous ? prevCaret : next ? nextCaret : children
        | _ => children
        };
      let wrapChildren = children => [|
        ReasonReact.createDomElement(
          "span",
          ~props={
            "aria-hidden": Js.Boolean.to_js_boolean(true),
            "key": "caret"
          },
          children
        ),
        ReasonReact.createDomElement(
          "span",
          ~props={"className": "sr-only", "key": "sr"},
          [|ReasonReact.stringToElement(ariaLabel)|]
        )
      |];
      let wrappedChildren =
        previous || next ? wrapChildren(children) : children;
      let className =
        [unwrapStr(i, className), "page-link"] |> String.concat(" ");
      ReasonReact.createDomElement(
        tag,
        ~props={
          "className": className,
          "aria-label": ariaLabel,
          "href": href,
          "onClick": Js.Nullable.fromOption(onClick)
        },
        wrappedChildren
      );
    }
    /* Create the default caret arrows */
    /* Use the default carets, if this is a prev or next and no children */
    /* A helper to wrap iff we are a prev or next element */
  };
};
