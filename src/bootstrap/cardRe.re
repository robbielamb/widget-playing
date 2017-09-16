include Utils;

include Colors;

let component = ReasonReact.statelessComponent "Card";

let make
    tag::(tag: string)="div"
    className::(className: option string)=?
    color::(color: option TextColor.t)=?
    backgroundColor::(backgroundColor: option BackgroundColor.t)=?
    borderColor::(borderColor: option BorderColor.t)=?
    children => {
  let classes =
    [
      "card",
      unwrapStr i className,
      TextColor.unWrap color,
      BackgroundColor.unWrap backgroundColor,
      BorderColor.unWrap borderColor
    ] |>
    String.concat " ";
  ReasonReact.createDomElement tag props::{"className": classes} children
};

module Body = {
  let component = ReasonReact.statelessComponent "Card.Body";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = ["card-body", unwrapStr i className] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Columns = {
  let component = ReasonReact.statelessComponent "Card.Columns";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = [unwrapStr i className, "card-columns"] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Deck = {
  let component = ReasonReact.statelessComponent "Card.Deck";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-deck"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Footer = {
  let component = ReasonReact.statelessComponent "Card.Footer";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-footer"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardGroup = {
  let component = ReasonReact.statelessComponent "Card.Group";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-group"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Header = {
  let component = ReasonReact.statelessComponent "Card.Header";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-header"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Img = {
  module Fixed = {
    type t =
      | None
      | Top
      | Bottom;
    let toString fixed =>
      switch fixed {
      | None => ""
      | Top => "-top"
      | Bottom => "-bottom"
      };
  };
  let component = ReasonReact.statelessComponent "Card.Img";
  let make
      tag::(tag: string)="img"
      src::(src: string)=""
      alt::(alt: string)=""
      fixed::(fixed: Fixed.t)=None
      className::(className: option string)=?
      children => {
    let classes = classNameReduce className [cn ("card-img" ^ Fixed.toString fixed)];
    ReasonReact.createDomElement tag props::{"className": classes, "src": src, "alt": alt} children
  };
};

module ImgOverlay = {
  let component = ReasonReact.statelessComponent "Card.ImgOverlay";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-img-overlay"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Link = {
  /* TODO: Handle href and proper callbacks */
  let component = ReasonReact.statelessComponent "Card.Link";
  let make tag::(tag: string)="a" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-link"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Title = {
  let component = ReasonReact.statelessComponent "Card.Title";
  let make tag::(tag: string)="h4" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-title"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Subtitle = {
  let component = ReasonReact.statelessComponent "Card.SubTitle";
  let make tag::(tag: string)="h6" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-subtitle"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module Text = {
  let component = ReasonReact.statelessComponent "Card.Text";
  let make tag::(tag: string)="p" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-text"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};